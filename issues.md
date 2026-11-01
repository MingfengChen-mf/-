# ROS2 新手任务避坑清单（发布端实践版）

> 适用场景：ROS2 Humble + Python（ament_python）功能包开发，覆盖自定义消息接口、colcon 构建、launch 多实例启动、跨终端联调。
> 条目统一采用 **症状 → 根因 → 预防/验证** 结构，按任务阶段归档。

---

## A. 接口定义阶段（msg 文件）

### A1｜接口文件路径错位

- **症状**：`rosidl_generate_interfaces() the passed file 'msg/Data.msg' doesn't exist relative to the CMAKE_CURRENT_SOURCE_DIR '.../包名'`
- **根因**：msg 文件未放置在**包根目录下的 `msg/`** 中。典型错误是多嵌套一层（如 `包名/src/msg/Data.msg`），而 CMake 查找的是 `包名/msg/Data.msg`
- **预防**：接口包（仅含 msg/srv/action）的目录规划为 `包名/msg/xxx.msg`，无需 `src/` 目录
- **验证**：

```bash
find ~/工作空间 -name "*.msg" -type f
```

### A2｜自定义接口依赖缺失

- **症状**：`ModuleNotFoundError: No module named 'xxx_interfaces'`（下游节点 import 接口包失败）
- **根因**：接口包的 `package.xml` 缺少 `rosidl_default_generators`（build_depend）与 `rosidl_default_runtime`（exec_depend）
- **预防**：自定义接口包创建后即补齐两行依赖；此为代码包交接时最高频的构建失败原因之一

### A3｜数组字段长度约束

- **决策**：定长场景使用 `float32[3]`，避免使用变长 `float32[]`
- **理由**：在接口层固定长度，下游解包（如 `a, b, c = msg.data`）不会因消息长度不符而抛异常——由类型系统在接口边界守门，优于在订阅端编写防御代码

---

## B. 构建阶段（colcon）

### B1｜构建目录与执行顺序

- **铁律**：`colcon build` 必须在 **workspace 根目录** 执行，而非 `src/` 内
- **顺序链**：修改代码 → `colcon build` → `source install/setup.bash` → `ros2 run` / `ros2 launch`，四步缺一不可

### B2｜构建脚本变更后的全清重建

- **铁律**：修改 `setup.py` / `CMakeLists.txt` / `package.xml` 后，必须全清缓存再构建：

```bash
rm -rf build install log
colcon build
```

- **症状**：entry point 已更名仍报旧错；或报 `AttributeError: 'NoneType' object has no attribute 'group'`（Traceback 停在 `load_entry_point`）
- **根因**：增量重建未刷新 egg-info 等注册元数据，新旧注册信息混杂

### B3｜entry_points 格式

- **格式铁律**：`'可执行名 = 包名.模块名:函数名'`，分隔符必须为冒号
- **症状**：launch 拉起进程立即退出，Traceback 止于 `importlib.metadata` 的 `load_entry_point`
- **易错点**：`.` 与 `:` 写混（如 `包.模块.函数`）；漏写 `:main`
- **验证**：

```bash
ros2 pkg executables 包名
```

注册表中存在的名称才可被 `ros2 run` 调用。

### B4｜launch 文件的注册链

- **规则**：launch 文件置于 `包根/launch/` 下，并在 `setup.py` 的 `data_files` 中注册：

```python
(os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
```

- **验证**：

```bash
ls install/包名/share/包名/launch/
```

能看到目标 launch 文件方为注册成功。

---

## C. 运行 / 联调阶段

### C1｜`No executable found` 与 `Package not found` 的区分

| 报错 | 含义 | 根因 |
|---|---|---|
| `Package 'xxx' not found` | ROS 环境未索引到该包 | 新包构建后未 `source install/setup.bash` |
| `No executable found` | 包已识别，但可执行名不存在 | `ros2 run` 第二个参数与 entry_points 注册名不一致 |

- **预防**：每个新终端均需 source，或将 `source ~/工作空间/install/setup.bash` 写入 `~/.bashrc`

### C2｜CLI 工具报接口类型 invalid

- **症状**：节点正常运行并发布，但 `ros2 topic echo` / `ros2 topic hz` 报 `The message type 'xxx/msg/Yyy' is invalid`
- **根因**：CLI 所在终端未 source，工作空间接口包不在其环境变量中（接口定义本身无问题）
- **验证**：

```bash
ros2 interface show 包名/msg/消息名
```

可打印定义 → 环境正常；报 invalid → 当前终端未 source。

### C3｜launch 文件名的全名匹配

- **症状**：`file 'pub_launch' was not found in the share directory of package 'xxx'`
- **根因**：`ros2 launch` 按全名匹配 launch 文件，调用时遗漏扩展名 `.py`

### C4｜launch 文件内的包名/可执行名一致性

- **症状**：launch 启动后报 `package 'yyy' not found, searching: [...]`
- **根因**：launch 文件中 `Node(package=..., executable=...)` 写入了占位符或与注册表不一致的名称（如沿用教程示例名）
- **规则**：launch 中的包名、可执行名必须与机器上的真实注册名完全一致
- **附带认知**：launch 中 `Node(name=...)` 会覆盖节点代码中 `super().__init__('...')` 的节点名；节点名（ROS 图标识）与自定义参数（业务编号）属两个维度，宜分开管理

### C5｜话题名命名规范

- **规则**：话题名不得以 `/` 结尾（触发 `expand_topic_name.c` 的 `is invalid` 报错），不得包含空名字段

### C6｜多进程日志阅读法

- **规则**：多实例 launch 产生的报错先做去重——N 段完全相同的 Traceback 对应单一根因，逐进程分别分析会造成"四处起火"的错觉
- **判据**：报错内容发生变化 = 故障已穿透当前层级（剥洋葱式推进），而非新增故障

---

## D. 元规则（凌驾于以上条目）

### D1｜报错路径是唯一真相来源

排查"文件存在却找不到"类问题时，应直接验证报错信息中给出的**确切绝对路径**，而非检查语义相近的目录。典型教训：文件位于 `包名/src/msg/`，CMake 查找的是 `包名/msg/`——两侧各说各话，永不交集。

### D2｜"文件存在 ≠ 系统找得到"

ROS2 的构件发现依赖注册表（`CMakeLists.txt` / `setup.py` / `package.xml`），而非文件系统本身。凡"存在却不可见"的故障，优先检查注册链路是否闭合。

### D3｜环境问题先于代码问题排除

跨终端调试时，每切换一个终端，先用 `ros2 interface show` 或 `ros2 pkg list` 验证环境，再进入代码排查。环境问题与代码问题的症状高度相似，先排除前者可节省约一半的排查时间。

---

## 故障定位速查表

| 现象 | 首查方向 |
|---|---|
| build 报 msg 文件不存在 | 文件是否位于 `包根/msg/`（A1） |
| import 接口包失败 | `package.xml` 依赖（A2）、当前终端是否 source（D3） |
| `No executable found` | entry_points 注册名（B3、C1） |
| launch 拉起即死 | entry_points 格式（B3）、launch 内包名/可执行名（C4） |
| echo 报类型 invalid | 该终端 source 状态（C2） |
| 多实例集体报错 | 日志去重，按单一根因处理（C6） |
| 改了配置仍报旧错 | `rm -rf build install log` 全清重建（B2） |
