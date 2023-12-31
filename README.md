Setup

# Set environment variables

source scripts/setvars.sh "bionic" (Not "trusty" as this leads to a different gcc version inside QEMU)

# Download and unzip linux-4.17

wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.17.tar.xz
tar xf linux-4.17.tar.xz

# Apply Patch

patch -s -p0 < file.patch

# Configure

cd linux-4.17
sudo make x86_64_defconfig

# Replace the run_qemu.sh with the attached script to allocate more memory and cpu to qemu

Benchmark
	
	# Compile the code for benchmark by running make inside the benchmark folder.
	# Run "./benchmark.o" to get the number of extents created for the user process.
	
