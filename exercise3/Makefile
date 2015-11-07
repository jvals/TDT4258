# Please put me in OSELAS.BSP-EnergyMicro-Gecko

.PHONY: setup


setup:
	ptxdist select configs/ptxconfig
	ptxdist platform configs/platform-energymicro-efm32gg-dk3750/platformconfig
	ptxdist toolchain /opt/ex3/OSELAS.Toolchain-2012.12.0/arm-cortexm3-uclinuxeabi/gcc-4.7.2-uclibc-0.9.33.2-binutils-2.22-kernel-3.6-sanitized/bin
	ptxdist images
	ptxdist test flash-all
