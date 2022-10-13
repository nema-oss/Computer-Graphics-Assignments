try:
    import wget
    NO_WGET=0
except ImportError as e:
    NO_WGET=1
    try:    
        import requests
    except ImportError as e2:
        print("\nOK, neither wget nor requests are installed. Install either of those first\n")
        print("If pip package manager is installed, running 'pip install wget' should get you everything you need")
        exit(1)
import os
import sys
import zipfile

def download_file(url, output_path):
    if NO_WGET == 1:
        r = requests.get(url, allow_redirects=True)
        with open(output_path, 'wb') as f:
            f.write(r.content)
    else:
        res = wget.download(url)
        os.rename(res, output_path)
    
    return output_path

def main(dva338_sourcedir):
    finalpath = os.path.abspath(dva338_sourcedir) + "/.."
    os.chdir(finalpath)
    print(f"Setting up common folder in {os.getcwd()}")
    os.makedirs("./Common/", exist_ok=True)
    os.chdir("./Common/")

    print("\nDownloading precompiled freeglut for windows")
    freeglut_win = download_file("https://www.transmissionzero.co.uk/files/software/development/GLUT/freeglut-MSVC-3.0.0-2.mp.zip", "freeglut.zip")
    with zipfile.ZipFile(freeglut_win, 'r') as zip_ref:
        zip_ref.extractall(".")
    print("\nDownloading precompiled GLEW for windows")
    glew_win = download_file("https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip", "GLEW.zip")
    with zipfile.ZipFile(glew_win, 'r') as zip_ref:
        zip_ref.extractall(".")
    
    print("\nOK, we've created the Common folder and downloaded both freeglut and GLEW.")


if __name__ == "__main__":
    if(len(sys.argv) > 1):
        main(sys.argv[1])
    else:
        print(f"Error: Usage is 'py {sys.argv[0]} <PATH_TO_DVA338_SOURCEDIR>")
