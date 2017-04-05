
###
# Docker script
#
# 1. Initial docker image
from ubuntu:16.10

# 2. Install dependancies
# 2.1 Install platform dependancies
run export DEBIAN_FRONTEND=noninteractive
run apt-get update
run apt-get install -y supervisor sudo ssh openssh-server software-properties-common wget openssl cmake
# The above is required to execute add-apt-repository
run sudo add-apt-repository -y ppa:team-gcc-arm-embedded/ppa
run sudo apt-get update -q
# 2.2 Install project dependancies
# 2.2.1 GCC ARM
run sudo apt-get install -y build-essential git openocd qemu-system-arm symlinks expect --force-yes
# 2.2.3 OpenOCD build dependancies
run sudo apt-get install -y libtool libftdi-dev libusb-1.0-0-dev automake pkg-config texinfo

# 2.2.4 Clone and init stm32 repository
run mkdir -p /home/admin
run cd /home/admin; git clone https://mateusz_s@bitbucket.org/mateusz_s/stm32libs.git

run mkdir /home/admin/downloads
run cd /home/admin/downloads; wget https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q3-update/+download/gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2
run pwd
run cd /usr/local; sudo tar xjf /home/admin/downloads/gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2
# 3. Add user admin with password "admin"
run useradd -s /bin/bash -m -d /home/admin -p $(openssl passwd -1 admin)  admin
run sed -Ei 's/adm:x:4:/admin:x:4:admin/' /etc/group
run sed -Ei 's/(\%admin ALL=\(ALL\) )ALL/\1 NOPASSWD:ALL/' /etc/sudoers

# 4. Setup ssh server
run mkdir -p /var/run/sshd
run /bin/echo -e "[program:sshd]\ncommand=/usr/sbin/sshd -D\n" > /etc/supervisor/conf.d/sshd.conf
expose 22

# 6. Build & Install OpenOCD from repository
# run cd /home/admin; git clone git://openocd.git.sourceforge.net/gitroot/openocd/openocd # Not Reliable
run cd /home/admin; git clone --depth 1 https://github.com/ntfreak/openocd.git
run cd /home/admin/openocd; ./bootstrap; ./configure --enable-maintainer-mode --disable-option-checking --disable-werror --prefix=/opt/openocd --enable-dummy --enable-usb_blaster_libftdi --enable-ep93xx --enable-at91rm9200 --enable-presto_libftdi --enable-usbprog --enable-jlink --enable-vsllink --enable-rlink --enable-stlink --enable-arm-jtag-ew; make -j4; make install

run sudo dpkg --add-architecture i386
run sudo apt-get update
run sudo apt-get install -y libc6:i386 libncurses5:i386 libstdc++6:i386

run touch /home/admin/.bashrc
run echo 'export STM32_LIBRARY_ROOT_DIR="/home/admin/stm32libs/spl_f4/Libraries"' >> /home/admin/.bashrc
run echo 'export ARM_TOOLCHAIN="/usr/local/gcc-arm-none-eabi-5_4-2016q3"' >> /home/admin/.bashrc
# 7. Post-install
# 7.1 Setup folder & file privileges
run chown -R admin:admin /home/admin
run chmod o+rx /home

run sudo add-apt-repository ppa:ubuntu-toolchain-r/test
run sudo apt-get update
run sudo apt-get install -y gcc-5 g++-5
run sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 1
run sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-5 1
run sudo apt-get install -y python-pip

run sudo apt-get install -y socat clang
run sudo pip install pyserial
run sudo pip install behave
run sudo mkdir /opt/qemu
run cd /opt; sudo wget https://github.com/gnuarmeclipse/qemu/releases/download/gae-2.7.0-20161128/gnuarmeclipse-qemu-debian64-2.7.0-201611282115-dev.tgz
run cd /opt; sudo tar xvf /opt/gnuarmeclipse-qemu-debian64-2.7.0-201611282115-dev.tgz qemu
run echo 'export STM_QEMU_PATH="/opt/qemu/2.7.0-201611282115-dev/"' >> /home/admin/.bashrc
run sudo pip install colorama behave
run sudo apt-get install -y clang-tidy

# 7.2 Commands to be executed when docker container starts
run sudo apt-get install -y ninja
run sudo echo '#!/bin/bash' >> /usr/bin/startup.sh
run sudo echo 'socat PTY,link=/dev/ttyS10,raw PTY,link=/dev/ttyS11,raw &' >> /usr/bin/startup.sh
run sudo echo 'sleep 1' >> /usr/bin/startup.sh
run sudo echo 'stty -F /dev/ttyS10 -onlcr && stty -F /dev/ttyS11 -onlcr' >> /usr/bin/startup.sh
run sudo echo 'chown admin /dev/ttyS10 && chown admin /dev/ttyS11'  >> /usr/bin/startup.sh
run sudo chmod +x /usr/bin/startup.sh

run sudo apt-get install -y gdb gdbserver
run sudo apt-get install -y lsof
cmd /usr/bin/startup.sh
