# 本次开发基本操作流程

> 适用场景：创建信息接口功能包和具体功能包、并将包运行成功

---

# 一、创建功能包

## 总体结构

```
ros2 pkg create 功能包名 --build-type 功能包具体类型 --dependencies 具体依赖 --license Apache-2.0
```

- `--license Apache-2.0` 固定的功能包开源协议
- `pkg` 表示功能包

## 实例1：信息接口包

```
ros2 pkg create 功能包名 --build-type ament_cmake --dependencies rosidl_default_generators builtin_interfaces --license Apache-2.0
```

- `rosidl_default_generators` 将消息文件转换为源码（注意：这是一个完整的包名，**中间不能有空格**，且是 `generators` 不是 `genorators`——包名里的空格在 shell 里意味着"两个参数"，命令会原样执行成功但静默建出缺依赖的包，直到 build 才炸）
- `builtin_interfaces` 提供 `Time` 等基础类型

## 实例2：发布包（python）

```
ros2 pkg create 功能包名 --build-type ament_python --dependencies rclpy 信息接口包名 --license Apache-2.0
```

- 功能包的依赖除了语言依赖等，必须加上对应信息接口（可以用官方，但更多用自己的）

# 二、重要操作：注册体系三分法

**先记住一个原则：注册表是主要矛盾，命令和路径都是它的表现形式。**
三类东西各有各的注册方式，卡壳时先问"这东西该在哪张注册表上登记"：

| 要注册的东西 | 注册位置 | 说明 |
|---|---|---|
| 节点代码（.py 里的 main） | `setup.py` 的 `entry_points` | 只适用于 `ament_python` |
| launch 文件（.py） | `setup.py` 的 `data_files` | 用 glob 收进 share 目录 |
| 消息接口（.msg） | `CMakeLists.txt` 的 `rosidl_generate_interfaces` | 只适用于 `ament_cmake` |

## 1. 节点代码的注册（ament_python）

在 `setup.py` 的 `entry_points` 中注册：

```
    entry_points={
        'console_scripts': [
            'data_pub = data_publisher.data_pub:main',
        ],
    },
```

- 等号左边是**可执行文件名**（`ros2 run` 时用的名字），**不是话题名**——话题名是代码里 `create_publisher` 决定的
- 等号右边的格式是 `功能包名.模块名:main`，其中"模块名"指节点文件名**不带 .py**
- 冒号必须是**半角 `:`**（全角 `：` 会直接 SyntaxError）
- 非最后一行末尾要加 `,`

## 2. launch 文件的注册（ament_python）

launch 文件**没有 main 函数，也不是节点**——它是被 `ros2 launch` 读取的"剧本"。
**绝不能注册进 `entry_points`**，注册成 console_script 会在运行时炸（找不到 main）。
正确方式只有一条：在 `setup.py` 的 `data_files` 里用 glob 收进来：

```
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
    ],
```

注意文件头部要先 `import os` 和 `from glob import glob`。

## 3. 消息接口的注册（ament_cmake）

在 `CMakeLists.txt` 中注册（下以信息接口包为例）：

```
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(builtin_interfaces REQUIRED)
# ===== 以下为新增 =====
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Data.msg"
  DEPENDENCIES builtin_interfaces
)
# ===== 新增结束 =====
```

**关于时间戳依赖要核对的点**：`builtin_interfaces` 提供的是 `Time` 基础类型——只有当 msg 文件里**直接写** `builtin_interfaces/Time xxx` 时才依赖它；如果 msg 文件写的是 `std_msgs/Header header`，依赖的应该是 `std_msgs`。
原则一句话：**依赖哪个包，取决于 msg 文件里引用了谁的类型**。对照自己的 `Data.msg` 实际内容核一遍。

## 4. 构建

```
colcon build
source install/setup.bash
```

- 每次修改完，都要重新 `colcon build`
- 每个终端的每次用到包的操作前，都要 `source ...`
- 若修改失败，要 `rm -rf install log build` 来清除缓存

**什么时候必须全清重建，什么时候可以偷懒**：

| 改了什么 | 处理方式 |
|---|---|
| Python 节点代码（.py） | 可免重建：用 `colcon build --symlink-install` 构建一次，之后改 .py 只需重新 `source` 即可生效 |
| `setup.py` / `package.xml` / `CMakeLists.txt` / `.msg` 文件 | **必须全清重建**：`rm -rf install log build && colcon build`，否则改了注册信息也不会生效（经典的"延迟爆发"坑） |

# 三、ros2话题通信常见查看命令

## （1）看节点 `ros2 node`

```
ros2 node list
ros2 node info /节点名
```

## （2）看话题 `ros2 topic`

```
ros2 topic list
ros2 topic list -t
ros2 topic info /话题名
ros2 topic echo /话题名
ros2 topic hz /话题名
ros2 topic bw /话题名
ros2 topic pub /话题名 消息类型 '{字段: 值}'
```

- `ros2 topic pub` 默认会以 **1Hz 持续发**，手动测试时一般要加 `--once`，否则话题上会一直挂着流量干扰排查

作用纵览：

| 命令 | 作用 |
|---|---|
| `ros2 topic list -t` | 列出话题，并显示消息类型 |
| `ros2 topic info` | 看话题类型、发布者数量、订阅者数量 |
| `ros2 topic echo` | 实时打印话题里的消息内容 |
| `ros2 topic hz` | 看发布频率 |
| `ros2 topic bw` | 看带宽占用 |
| `ros2 topic pub` | 手动向话题发一条消息 |

## （3）看包与接口

```
ros2 pkg executables 包名          # 列出包的注册可执行文件（验证 entry_points 是否生效）
ros2 interface show 消息类型       # 查看消息类型的字段定义（验证接口是否正确生成）
```

## （4）排查顺序参考

```
ros2 node list
ros2 topic list -t
ros2 topic info /xxx
ros2 topic echo /xxx
ros2 node info /节点名
ros2 interface show 消息类型
```

# 四、注意事项

- `-` 和 `_` 一定不要搞混
- 写代码时一定要注意名称对应，不要搬代码忘了改了（包名、接口名...）
- 要注意当前行为所在目录（如 `colcon build` 一定要在总工作空间目录，而非 `/src` 源码目录）
- console_script 入口只给有 `main` 的节点代码用；launch 文件走 `data_files`；msg 文件走 CMakeLists 的 `rosidl_generate_interfaces`——注册体系三分法，别混

---

<祝看到这里的人开发顺利！
