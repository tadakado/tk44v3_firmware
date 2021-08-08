# Firmware for tk44v3 keyboard

## How to make

1. build environment

```
cd /home
git clone --depth 1 -b bmp-0.10.1 https://github.com/sekigon-gonnoc/qmk_firmware.git qmk_firmware_bmp
cd qmk_firmware_bmp
./util/qmk_install.sh
```

2. compile the firmware

```
cd /home/qmk_firmware_bmp
mkdir /media
export USER=
make tk44v3:default:uf2
cp tk44v3_default.uf2 /some/where/foo.uf2
```

## notes

BLE status works only on bmp-0.10.1.
