# Fractaleidoscope

Psychedelic installation !!

## get started: 


### install openGL

sudo apt-get install freeglut3 freeglut3-dev

### install GLEW

sudo apt-get install build-essential libxmu-dev libxi-dev libgl-dev libosmesa-dev

git clone git@github.com:nigels-com/glew.git

cd glew

make

sudo make install

make clean

### install openCV

sudo apt-get install build-essential

sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev

git clone git@github.com:opencv/opencv.git

cd ./opencv

cmake .

make 

sudo make install

### build and run the project:

cd opengl/

cmake .

make

./fractal


#### TODO: Use camera Stream::

https://r3dux.org/2012/01/how-to-convert-an-opencv-cvmat-to-an-opengl-texture/


