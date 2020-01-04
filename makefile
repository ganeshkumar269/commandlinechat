LIBS =  -lcurl -lssl -lcrypto -lz -lwldap32 -lws2_32 -lwinmm -lgdi32
INCLUDE_DIR = -I./dependencies/include
LIB_DIR = -L./dependencies/lib
LOCAL_INCLUDE_DIR = -I./include


all: main.o functions.o inputParse.o
	mingw32-g++.exe -Wall -std=c++14 -DCURL_STATICLIB ./obj/main.o ./obj/functions.o ./obj/getMessages.o ./obj/fileupload.o ./obj/checkspeed.o ./obj/inputParse.o -o ./bin/clc.exe $(LIB_DIR) $(LIBS)
main.o:
	mingw32-g++.exe -c -Wall -std=c++14 -DCURL_STATICLIB main.cpp -o ./obj/main.o $(INCLUDE_DIR) $(LOCAL_INCLUDE_DIR)
functions.o: getMessages.o fileupload.o checkspeed.o
	mingw32-g++.exe -c -Wall -std=c++14 -DCURL_STATICLIB ./src/functions.cpp -o ./obj/functions.o $(INCLUDE_DIR) $(LOCAL_INCLUDE_DIR)
inputParse.o:
	mingw32-g++.exe -c -Wall -std=c++14 -DCURL_STATICLIB ./src/inputParse.cpp -o ./obj/inputParse.o $(INCLUDE_DIR) $(LOCAL_INCLUDE_DIR)
getMessages.o:
	mingw32-g++.exe -c -Wall -std=c++14 -DCURL_STATICLIB ./src/getMessages.cpp -o ./obj/getMessages.o $(INCLUDE_DIR) $(LOCAL_INCLUDE_DIR)
fileupload.o:
	mingw32-g++.exe -c -Wall -std=c++14 -DCURL_STATICLIB ./src/fileupload.cpp -o ./obj/fileupload.o $(INCLUDE_DIR) $(LOCAL_INCLUDE_DIR)
checkspeed.o:
	mingw32-g++.exe -c -Wall -std=c++14 -DCURL_STATICLIB ./src/check_speed.cpp -o ./obj/checkspeed.o $(INCLUDE_DIR) $(LOCAL_INCLUDE_DIR)
http2_upload:
	mingw32-g++.exe -Wall -std=c++14 -DCURL_STATICLIB ./src/http2_upload.c -o ./bin/http2_upload.exe $(INCLUDE_DIR) $(LIBS)
clean:
	rm ./obj/*.o
test: inputParse.o
	mingw32-g++.exe -Wall -std=c++14 -DCURL_STATICLIB  ./src/inputParse.cpp ./test/test.cpp -o ./bin/test.exe $(INCLUDE_DIR) $(LOCAL_INCLUDE_DIR)


