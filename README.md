```
apt-get install build-essential
apt-get install libcurl4-openssl-dev
apt-get install cmake
apt-get install git
apt-get install ctags
apt-get install libasound2-dev
apt-get install pkg-config

git clone https://github.com/jchavanton/voip_perf.git
cd voip_perf
git submodule update --init
cd pjsua/
./configure
make dep
make
make install
cd ..
cmake CMakeLists.txt
make

./voip_perf
```

