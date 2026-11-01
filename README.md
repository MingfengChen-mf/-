# data_publisher 功能包交接说明

> ROS 2 demo 通讯学习应用 —— 发布方工作空间（5 个发布节点，5Hz，报文带时间戳 + 三维数组）
> 维护者：mingfeng（cn_stu_mf@outlook.com）｜许可证：Apache-2.0

---

## 1. 功能概述

本工作空间包含两个功能包：

| 包名 | 构建类型 | 作用 |
|---|---|---|
| `status_interfaces` | ament_cmake | 自定义消息接口包，定义 `msg/Data.msg` |
| `data_publisher` | ament_python | 发布包，含 5 个发布节点与启动文件 |

发布节点行为：

- 消息类型：`status_interfaces/msg/Data`（自定义接口）
- 话题名称：`/node1` ~ `/node5`（由参数 `node_id` 决定）
- 发布频率：5 Hz（定时器周期 0.2 s）
- 队列深度（QoS）：10
- 发布内容：当前时间戳 + 3 个取值范围为 [-20, 20] 的均匀分布随机浮点数

本实现依据 `任务要求.md`：每人写五个发布节点，报文需带时间标识，频率固定 5Hz，每条报文为三维数组且数组内至少一个数字变化。

## 2. 目录结构

```
.
├── src/
│   ├── data_publisher/
│   │   ├── data_publisher/
│   │   │   ├── data_pub.py        # 发布节点实现
│   │   │   └── __init__.py
│   │   ├── launch/
│   │   │   └── pub_launch.py      # 一次启动 5 个节点的 launch 文件
│   │   ├── resource/data_publisher
│   │   ├── test/                  # flake8 / copyright / pep257 测试
│   │   ├── LICENSE
│   │   ├── package.xml
│   │   ├── setup.cfg
│   │   └── setup.py
│   └── status_interfaces/
│       ├── CMakeLists.txt
│       ├── include/status_interfaces/
│       ├── LICENSE
│       ├── msg/
│       │   └── Data.msg
│       └── package.xml
├── build/  install/  log/          # colcon 构建产物（已被.gitignore忽略）
├── 任务要求.md                      # 本次练习任务书
├── fundemental_procedure.md        # 开发操作流程笔记（含注册体系三分法）
├── issues.md                       # 问题记录
└── README.md                       # 本文件
```

## 3. 自定义消息接口（status_interfaces/msg/Data）

```
builtin_interfaces/Time stamp #记录时间戳
float32[3] data_group         #所需三维数组
```

- `stamp`：记录时间戳（`builtin_interfaces/Time` 类型）
- `data_group`：长度为 3 的 float32 数组，三个元素按任务要求对应报文结构 `a b c`（顺序对应关系见第 8.2 节）

接口包 `CMakeLists.txt` 已通过 `rosidl_generate_interfaces` 注册 `msg/Data.msg`，依赖 `rosidl_default_generators` 与 `builtin_interfaces`。

## 4. 节点实现（data_publisher/data_pub.py）

- 节点类：`DataPub`，默认节点名 `data_pub`（launch 中重命名为 `data_pub_{id}`）
- 参数：
  - `node_id`：整型，默认值为 `1`。话题名拼接为 `/node{node_id}`。
- 定时器：0.2 s（即 5 Hz），每次回调中：
  1. 用 `self.get_clock().now().to_msg()` 填充 `msg.stamp`
  2. 循环 3 次调用 `random.uniform(-20, 20)` 生成随机数，填入 `msg.data_group`
  3. 发布消息，并通过 `get_logger().info` 打印日志（含完整消息）
- 代码注释说明：三维数组在每次回调时现场生成；也可用列表生成式 `[random.uniform(-20, 20) for _ in range(3)]` 替代。

入口函数 `main()`：初始化 rclpy → 创建节点 → spin → 销毁节点 → shutdown。

## 5. 启动文件（launch/pub_launch.py）

- 生成 5 个 `data_pub` 节点实例（`for i in range(1, 6)`）
- 每个节点：`package='data_publisher'`，`executable='data_pub'`，参数 `{'node_id': i}`，重命名为 `data_pub_1` ~ `data_pub_5`
- 对应话题为 `/node1` ~ `/node5`

## 6. 构建配置

### 6.1 setup.py（data_publisher，ament_python）

| 项目 | 内容 |
|---|---|
| 版本 | 0.0.0 |
| 许可证 | Apache-2.0 |
| 描述 | TODO: Package description（尚未填写） |
| 安装依赖 | setuptools |
| 测试 extras | pytest |

console_scripts 入口点：

```python
'console_scripts': [
    'data_pub = data_publisher.data_pub:main'
],
```

> **注意**：原先误注册的 `'pub_launch = data_publisher.pub_launch:main'` 已删除。launch 文件不是节点、没有 `main`，不能注册进 console_scripts；其正确注册方式是 `setup.py` 的 `data_files` 中用 glob 收进 share 目录（本仓库已正确配置）。

data_files：`resource/data_publisher`（ament 索引）、`package.xml`、`launch/*.py`。

### 6.2 package.xml 依赖

- `data_publisher`：`rclpy`、`status_interfaces`
- `status_interfaces`：`rosidl_default_generators`、`builtin_interfaces`，并声明 `<member_of_group>rosidl_interface_packages</member_of_group>`

## 7. 克隆后构建与运行流程

### 7.1 前提

- 已安装 ROS 2 Humble（本仓库实测环境为 Ubuntu + Python 3.10）
- 两个功能包必须放在**同一个工作空间的 `src/` 目录下**一起构建（`data_publisher` 依赖 `status_interfaces`）

### 7.2 构建

```bash
cd <工作空间根目录>        # 必须在总工作空间目录执行，不能在 src/ 里
colcon build
source install/setup.bash  # 每个新终端都要执行
```

- 改 `.py` 节点代码可先用 `colcon build --symlink-install`，之后改代码只需重新 `source`
- 改 `setup.py` / `package.xml` / `CMakeLists.txt` / `.msg` 后必须 `rm -rf install log build && colcon build` 全清重建
- 详见 `fundemental_procedure.md` 第"二、重要操作"节

### 7.3 运行

```bash
ros2 launch data_publisher pub_launch.py
```

启动后出现 5 个节点：`data_pub_1` ~ `data_pub_5`。

### 7.4 验证（发布方自检，已实测通过）

```bash
ros2 node list                      # 应看到 data_pub_1 ~ data_pub_5
ros2 topic list -t                  # 应看到 /node1 ~ /node5，类型 status_interfaces/msg/Data
ros2 topic echo /node1              # 实时查看 stamp + data_group
ros2 topic hz /node1                # 实测约 5.0 Hz（min 0.198s / max 0.203s）
ros2 interface show status_interfaces/msg/Data
ros2 pkg executables data_publisher # 验证注册的可执行文件
```

排查顺序参考：`ros2 node list` → `ros2 topic list -t` → `ros2 topic info /xxx` → `ros2 topic echo /xxx` → `ros2 node info /节点名` → `ros2 interface show 消息类型`。

## 8. 给订阅方（代码接收方）的对接提醒

依据 `任务要求.md`，接收方需编写两个计算节点和一个最终订阅者。对接要点：

### 8.1 必须复用本仓库的消息接口包

- 订阅的消息类型为 **`status_interfaces/msg/Data`**：
  - `builtin_interfaces/Time stamp`：记录时间戳
  - `float32[3] data_group`：三维数组
- 订阅功能包须在 `package.xml` 声明 `<depend>status_interfaces</depend>`，代码中 `from status_interfaces.msg import Data` 导入。
- 接口包是 `ament_cmake` 类型，**须与本发布包放同一工作空间一起 `colcon build`**，否则消息类型无法找到。
- 对方包若是 `ament_python`，注意 `setup.py` 的 `install_requires` 只有 `setuptools`，运行期依赖靠 `package.xml` 的 `<depend>` 保证 colcon 构建顺序。

### 8.2 话题与数据对应关系

- 本发布包共 5 个话题：`/node1` ~ `/node5`，编号即发布节点的 `node_id`。
- 按任务要求"每条报文的结构为 a b c"，三维数组 `data_group` 的三个元素即 a、b、c，按数组顺序对应（`data_group[0]→a`、`[1]→b`、`[2]→c`）。
- 按任务要求的取数约定：
  - **计算节点 1**：订阅 `/node1`、`/node2`、`/node3`，按 `(a1+a2+a3) - (b1+b2+b3) + (c1+c2+c3)` 制表输出（下标 1~3 对应 /node1~/node3）
  - **计算节点 2**：订阅 `/node4`、`/node5`，按 `(a4+b4) * (a5-b5)` 制表输出（下标 4、5 对应 /node4、/node5）
  - **最终订阅者**：捕获计算节点 1 和节点 2 输出的实时值（这两个输出话题由接收方自行定义，本仓库不涉及）

### 8.3 数据与频率特性

- 发布频率 5Hz（定时器 0.2s），实测约 5.0 Hz。
- 各节点回调相互独立、无跨节点同步机制，五个话题的数据并非严格同一时刻采样；`stamp` 为各节点各自发布时刻的时钟时间，可作为对齐参考。
- 数据为 [-20, 20] 均匀分布随机数，每次回调三个元素均独立重新生成，满足"数组内至少一个数字变化"的要求。
- QoS 队列深度 10，未设置其他策略；订阅端用默认 QoS 即可匹配。

### 8.4 通用注意事项

- `-` 和 `_` 不要搞混（包名均为下划线）。
- 搬代码时注意名称对应：包名、接口名、话题名不要忘改。
- `colcon build` 必须在工作空间根目录执行。
- 每个用到包的终端操作前都要 `source install/setup.bash`。
- ament_python 包的 console_scripts 注册格式：`'可执行文件名 = 功能包名.节点模块名:main'`（半角冒号，非最后一行加逗号）；launch 文件走 `data_files`，msg 文件走 `CMakeLists.txt` 的 `rosidl_generate_interfaces`（详见 `fundemental_procedure.md` 的"注册体系三分法"）。

## 9. 已知遗留问题


1. `data_pub.py` 中日志以 `info` 级别打印完整消息，5 节点 5Hz 下终端输出量较大，调试时可用 `ros2 launch ... > /dev/null` 重定向。
