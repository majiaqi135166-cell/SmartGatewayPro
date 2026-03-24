cat <<EOF > README.md
# SmartGatewayPro

基于 Orange Pi Zero 3 的嵌入式智能网关项目。

## 核心功能
- **多线程架构**：主线程负责传感器采集与控制，子线程负责网络通讯。
- **状态机控制**：支持 SAFE/WARNING/CRITICAL 三级温度预警。
- **配置驱动**：支持通过 \`gateway.conf\` 动态配置 IP、端口及阈值。
- **单例日志系统**：线程安全的日志记录，支持自动刷盘。

## 目录结构
- \`src/\`: 源代码 (.cpp)
- \`include/\`: 头文件 (.hpp)
- \`gateway.conf\`: 配置文件

## 编译运行
\`\`\`bash
mkdir build && cd build
cmake ..
make
./gateway
\`\`\`
EOF

# 提交并更新 README
git add README.md
git commit -m "Update README.md"
git push origin main
