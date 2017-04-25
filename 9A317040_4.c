#include < stdio.h >
#include < stdlib.h >
void main(int argc, char *argv[])
{
 int filelen;
 FILE *input,*output;
 if ( argc < 3 )
 {
  printf("Usage:%s source dest\n",argv[0]);
  exit(0);
 }
 // 開啟檔案
 if( (input=fopen(argv[1],"rb"))==NULL )
 {
  printf("open %s fail!\n",argv[2]);
  exit(0);
 }
 if( (output=fopen(argv[2],"wb"))==NULL )
 {
  printf("open %s fail!\n",argv[3]);
  exit(0);
 }
 fseek( input, 0, SEEK_END);
 filelen = ftell( input );
 fseek( input, 0, SEEK_SET);
 unsigned char *data=new unsigned char[filelen]; // 配置一塊可以讀整個檔案的空間
 fread( data, 1, filelen, input ); // 把整個檔案讀進記憶體
 fwrite( data, 1, filelen, output ); // 把整個檔案寫到另一個檔案中
 fclose( input );
 fclose( output );
}
