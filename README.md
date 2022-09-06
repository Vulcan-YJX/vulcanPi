# vulcanPi
给自己挖的一个新坑，目标是在 `X3Pi` 平台实现 `wiringPi` 的全部功能。

个人能力有限，此项目会优先上传一些新的功能，但是并不能保证其稳定性。如需使用经过测试且稳定的功能，请使用[长期支持版本。](https://github.com/DDTRobot/vulcanPi)

## 一、安装

```bash
git clone https://github.com/Vulcan-YJX/vulcanPi.git
cd vulcanPi && mkdir build
cd build && cmake ..
make
sudo make install
```

注：目前缺少 `cmake_config` ，`CMake` 中 `vulcanPi_FOUND` 是找不到的，请手动配置。

## 二、功能

- 支持串口
- 支持 SPI
- 支持基础 IO 控制



## 三、计划

1. 增加 readall

2. 增加 iic 支持

3. 增加 9g 蓝色小舵机支持

4. 增加 imu 传感器读数支持

   

## 四、声明

此项目仅用于个人开发测试。

如需商用请联系长期支持版所在组织。
