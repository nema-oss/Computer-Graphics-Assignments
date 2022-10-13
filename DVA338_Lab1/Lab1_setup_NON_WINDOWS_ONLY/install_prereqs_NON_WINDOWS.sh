#/bin/sh
# Script that builds and deploys freeglut and GLEW to a local directory
# Assumes CMake is installed
#These are the latest versions at time of writing this script
FREEGLUT_VERSION="3.2.2"
GLEW_VERSION="2.1.0"

if [[ $# -eq 0 ]]; then
  echo "Usage: $0 <path_to_Commons_Folder>"
  echo "If you plan to use cmake to build the lab skeleton"
  echo "then please use the same structure as in the lab startup document"
  echo "DevOgl"
  echo "    Common <-- Common is here"
  echo "    DVA338_Lab1" 
  echo "       Lab1_setup_NON_WINDOWS_ONLY"
  echo "           <this script is here>"
  echo "       models"
  echo "       test"
  exit
fi

CMAKE_PATH=`which cmake`
BASE_DIR="$1"
INSTALL_DIR="${BASE_DIR}/Installs"

mkdir -p "${INSTALL_DIR}"

wget "http://prdownloads.sourceforge.net/freeglut/freeglut-${FREEGLUT_VERSION}.tar.gz"
tar -xvf "freeglut-${FREEGLUT_VERSION}.tar.gz"
if [[ -z "$CMAKE_PATH" ]]; then
    echo "For now, we support CMake for generating build scripts. You can likely install it using 'apt-get install cmake'"
    exit 1
fi
cd "freeglut-${FREEGLUT_VERSION}"
mkdir "cmakebuild" && cd "cmakebuild"
#We assume the standard make build system. Feel free to change to whichever you prefer
cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR}" ..

make && make install
RESULT=$?
if [ $RESULT -eq 0 ]; then
  echo "Great! Freeglut should now be available in ${INSTALL_DIR}"
else
  echo "Something went wrong. Please check any errors, and if necessary install freeglut manually into e.g. ${INSTALL_DIR}"
fi

#INSTALL GLEW

cd "$BASE_DIR"
wget "https://sourceforge.net/projects/glew/files/glew/${GLEW_VERSION}/glew-${GLEW_VERSION}.tgz"
tar -xvf "glew-${GLEW_VERSION}.tgz"

cd "glew-${GLEW_VERSION}"
mkdir "cmakebuild" && cd "cmakebuild"
#We assume the standard make build system. Feel free to change to whichever you prefer
cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR}" ../build/cmake
make && make install
RESULT=$?
if [ $RESULT -eq 0 ]; then
  echo "Great! GLEW should now be available in ${INSTALL_DIR}"
else
  echo "Something went wrong. Please check any errors, and if necessary install glew manually into e.g. ${INSTALL_DIR}"
fi

cd "$BASE_DIR"