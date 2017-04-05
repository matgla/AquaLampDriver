sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install -y git build-essential openocd qemu-system-arm symlinks expect libtool libftdi-dev libusb-1.0-0-dev automake pkg-config texinfo
sudo mkdir -p /opt/arm_sdk
cd /opt/arm_sdk
sudo git clone https://mateusz_s@bitbucket.org/mateusz_s/stm32libs.git
sudo wget https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q3-update/+download/gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2
sudo tar xjvf gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2
sudo rm gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2

sudo dpkg --add-architecture i386
sudo apt-get install -y libc6:i386 libncurses5:i386 libstdc++6:i386 --force-yes

echo 'export STM32_LIBRARY_ROOT_DIR="/opt/arm_sdk/stm32libs/spl_f4/Libraries"' >> ~/.bashrc
echo 'export ARM_TOOLCHAIN="/opt/arm_sdk/local/gcc-arm-none-eabi-5_4-2016q3"' >> ~/.bashrc

sudo apt-get install -y gcc-5 g++-5 python-pip socat clang clang-tidy gdb gdbserver  --force-yes
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 1
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-5 1
sudo pip install pyserial behave colorama behave

cd /opt/arm_sdk
sudo wget https://github.com/gnuarmeclipse/qemu/releases/download/gae-2.7.0-20161128/gnuarmeclipse-qemu-debian64-2.7.0-201611282115-dev.tgz
sudo tar xvf gnuarmeclipse-qemu-debian64-2.7.0-201611282115-dev.tgz qemu
sudo rm gnuarmeclipse-qemu-debian64-2.7.0-201611282115-dev.tgz
echo 'export STM_QEMU_PATH="/opt/arm_sdk/qemu/2.7.0-201611282115-dev/"' >> ~/.bashrc

