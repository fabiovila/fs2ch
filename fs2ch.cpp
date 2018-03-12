#include <iostream>
#include "boost/filesystem.hpp"
#include <fstream>
#include <map>
#include <cstring>
#include <string>


/* Embed recursively files in current folder or path in a C struct
 * 
 * struct { 
 * char *name; 					- NULL terminated name filename
 * char *mime; 					- NULL terminated string with MIME type is possible
 * int size; 					- size of file
 * char *data; 					- File's bytes
 * } fsFiles[ FILES FOUND ];	- array with files embedded
 * 
 * #define FS_FILES				- SIZE OF fsFiles array. ( Number of files stored )
 * 
 * 
 * out.h						- Output C include with all files found embedded. Just include it in your aplication
 * */

// Fabio Vila
// chefvila@yahoo.com.br
// https://github.com/fabiovila

// Compile with:
// g++ -lstdc++ -lboost_system -lboost_filesystem fs2ch.cpp  -o fs2hc
// or just make

using namespace std;
using namespace boost::filesystem;
std::vector <std::string> List;


std::map <std::string,std::string> mime();
std::map <std::string,std::string> MIMELIST;

/* py
>>> for i in range(256):
...     print("{\"\\\\"+hex(i)+"\"},", end='')
*/
const string dec2hex[] = {{"\\x0"},{"\\x1"},{"\\x2"},{"\\x3"},{"\\x4"},{"\\x5"},{"\\x6"},{"\\x7"},{"\\x8"},{"\\x9"},{"\\xa"},{"\\xb"},{"\\xc"},{"\\xd"},{"\\xe"},{"\\xf"},{"\\x10"},{"\\x11"},{"\\x12"},{"\\x13"},{"\\x14"},{"\\x15"},{"\\x16"},{"\\x17"},{"\\x18"},{"\\x19"},{"\\x1a"},{"\\x1b"},{"\\x1c"},{"\\x1d"},{"\\x1e"},{"\\x1f"},{"\\x20"},{"\\x21"},{"\\x22"},{"\\x23"},{"\\x24"},{"\\x25"},{"\\x26"},{"\\x27"},{"\\x28"},{"\\x29"},{"\\x2a"},{"\\x2b"},{"\\x2c"},{"\\x2d"},{"\\x2e"},{"\\x2f"},{"\\x30"},{"\\x31"},{"\\x32"},{"\\x33"},{"\\x34"},{"\\x35"},{"\\x36"},{"\\x37"},{"\\x38"},{"\\x39"},{"\\x3a"},{"\\x3b"},{"\\x3c"},{"\\x3d"},{"\\x3e"},{"\\x3f"},{"\\x40"},{"\\x41"},{"\\x42"},{"\\x43"},{"\\x44"},{"\\x45"},{"\\x46"},{"\\x47"},{"\\x48"},{"\\x49"},{"\\x4a"},{"\\x4b"},{"\\x4c"},{"\\x4d"},{"\\x4e"},{"\\x4f"},{"\\x50"},{"\\x51"},{"\\x52"},{"\\x53"},{"\\x54"},{"\\x55"},{"\\x56"},{"\\x57"},{"\\x58"},{"\\x59"},{"\\x5a"},{"\\x5b"},{"\\x5c"},{"\\x5d"},{"\\x5e"},{"\\x5f"},{"\\x60"},{"\\x61"},{"\\x62"},{"\\x63"},{"\\x64"},{"\\x65"},{"\\x66"},{"\\x67"},{"\\x68"},{"\\x69"},{"\\x6a"},{"\\x6b"},{"\\x6c"},{"\\x6d"},{"\\x6e"},{"\\x6f"},{"\\x70"},{"\\x71"},{"\\x72"},{"\\x73"},{"\\x74"},{"\\x75"},{"\\x76"},{"\\x77"},{"\\x78"},{"\\x79"},{"\\x7a"},{"\\x7b"},{"\\x7c"},{"\\x7d"},{"\\x7e"},{"\\x7f"},{"\\x80"},{"\\x81"},{"\\x82"},{"\\x83"},{"\\x84"},{"\\x85"},{"\\x86"},{"\\x87"},{"\\x88"},{"\\x89"},{"\\x8a"},{"\\x8b"},{"\\x8c"},{"\\x8d"},{"\\x8e"},{"\\x8f"},{"\\x90"},{"\\x91"},{"\\x92"},{"\\x93"},{"\\x94"},{"\\x95"},{"\\x96"},{"\\x97"},{"\\x98"},{"\\x99"},{"\\x9a"},{"\\x9b"},{"\\x9c"},{"\\x9d"},{"\\x9e"},{"\\x9f"},{"\\xa0"},{"\\xa1"},{"\\xa2"},{"\\xa3"},{"\\xa4"},{"\\xa5"},{"\\xa6"},{"\\xa7"},{"\\xa8"},{"\\xa9"},{"\\xaa"},{"\\xab"},{"\\xac"},{"\\xad"},{"\\xae"},{"\\xaf"},{"\\xb0"},{"\\xb1"},{"\\xb2"},{"\\xb3"},{"\\xb4"},{"\\xb5"},{"\\xb6"},{"\\xb7"},{"\\xb8"},{"\\xb9"},{"\\xba"},{"\\xbb"},{"\\xbc"},{"\\xbd"},{"\\xbe"},{"\\xbf"},{"\\xc0"},{"\\xc1"},{"\\xc2"},{"\\xc3"},{"\\xc4"},{"\\xc5"},{"\\xc6"},{"\\xc7"},{"\\xc8"},{"\\xc9"},{"\\xca"},{"\\xcb"},{"\\xcc"},{"\\xcd"},{"\\xce"},{"\\xcf"},{"\\xd0"},{"\\xd1"},{"\\xd2"},{"\\xd3"},{"\\xd4"},{"\\xd5"},{"\\xd6"},{"\\xd7"},{"\\xd8"},{"\\xd9"},{"\\xda"},{"\\xdb"},{"\\xdc"},{"\\xdd"},{"\\xde"},{"\\xdf"},{"\\xe0"},{"\\xe1"},{"\\xe2"},{"\\xe3"},{"\\xe4"},{"\\xe5"},{"\\xe6"},{"\\xe7"},{"\\xe8"},{"\\xe9"},{"\\xea"},{"\\xeb"},{"\\xec"},{"\\xed"},{"\\xee"},{"\\xef"},{"\\xf0"},{"\\xf1"},{"\\xf2"},{"\\xf3"},{"\\xf4"},{"\\xf5"},{"\\xf6"},{"\\xf7"},{"\\xf8"},{"\\xf9"},{"\\xfa"},{"\\xfb"},{"\\xfc"},{"\\xfd"},{"\\xfe"},{"\\xff"}}; 

struct stFile {
	std::string 	name;
	char 			*bytes;
	int 			size;
	string			mime;
};
	
string getmime( string filename ){
	
	string ext = filename.substr(filename.find_last_of(".") + 1);

	if (MIMELIST[ext] == "" ) return "application/octet-stream"; else return MIMELIST[ext];
} 

void listfolder(const std::string& path)
{
	
    if (!path.empty())
    {
        namespace fs = boost::filesystem;

        fs::path apk_path(path);
        fs::recursive_directory_iterator end;

        for (fs::recursive_directory_iterator i(apk_path); i != end; ++i)
        {
            const fs::path cp = (*i);
            List.push_back(cp.string());
        }
    }
    return;
}

int main(int argc, char *argv[])
{
	
  std::vector <stFile> Files;
  stFile tFiles;
  char chBuffer[100];
  string path;
  string outputname;
  MIMELIST = mime();
  
  if (argc <= 1) {
	  boost::filesystem::path cpath(boost::filesystem::current_path());	
	  path = cpath.string();
	} else {
		path = argv[1];
	}

   if (argc == 3){
	   outputname = argv[2];
	   
   } else outputname = "out.h";
  cout << "Input directory \e[92m" << path << "\e[0m\n";
  cout << "Output file as \e[92m" << outputname << "\e[0m\n";
  cout << "\e[1mMounting the filesystem ..." << "\e[0m\n";
  listfolder(path);
  
  for (std::vector<std::string>::const_iterator i = List.begin(); i != List.end(); ++i){
	if (!boost::filesystem::is_regular_file(*i)) continue; // Opened files return undefined length 
		std::ifstream file(*i, std::ios::binary );
		if (file) {
					// Get file size
					std::uintmax_t  length = boost::filesystem::file_size(*i);
					// Alloc buffer
					//cout << *i << " " << length << " " << boost::filesystem::is_regular_file(*i) << " " << boost::filesystem::file_size(*i);
					char * buffer = new char [length];
					// Read and store name and size
					file.read(buffer,length);
						tFiles.name = *i;
						// clear path
						tFiles.name = tFiles.name.substr(path.size(),tFiles.name.size());
						tFiles.mime = getmime(tFiles.name);
						tFiles.bytes = buffer;
						tFiles.size = length;					  
						Files.push_back(tFiles);
					file.close();
		} else exit(1);
	} 

	// Create out.h 
	 std::ofstream out(outputname);
	 int index = 0, a = 0;
	 cout << " Creating \e[92m"<< outputname << "\e[0m file ... \n";
	 out << "typedef struct { const char *name; const char *mime; int size; const unsigned char *data; } stFile;\n";
	 out << "#define FS_FILES	" << Files.size() << "\n";

	 
	 index = 0;
	 for (std::vector<stFile>::iterator i = Files.begin(); i != Files.end(); ++i) {
		 out << "// " << index << " : " << i->name  << " " << i->mime << " " << i->size << "\n";
		 index++;
	 }
	 
	 
	 out << "\n\nconst volatile stFile fsFiles[" << Files.size() <<"] = { "; 
	 

	 for (std::vector<stFile>::iterator i = Files.begin(); i != Files.end(); ++i){
		 cout << " " << i->name << "\n";
		 
		 out << "{\"" << i->name << "\" , ";
		 out << "\"" << i->mime << "\" , ";
		 out << i->size << ", ";
		 out << "(const unsigned char*)\""; 
			for (a = 0; a < i->size; a++) {
				out << dec2hex[(unsigned char) i->bytes[a]];	
			}
		if ( Files.end() - i == 1 ) out << "\"}"; else out << "\"}, "; 		
		 
	 }
	out << "};"; 
	out.close();
	cout << "\n\e[1mFiles embedded: " << Files.size() <<  " in struct: \e[0m\n";
	cout << " \e[96mstruct {\n  const char *name; \n  const char *mime; \n  int size; \n  const unsigned char *data;\n };\e[0m\n";
	cout << "\n\e[1mInclude \e[92m" << outputname <<  "\e[0m in your application and use fsFiles["<< Files.size() << "]\n\n\n\e[0m";
}

std::map <std::string,std::string> mime (void){
std::map <std::string,std::string> MIMELIST {
{ "3dm","x-world/x-3dmf"},
{ "3dmf","x-world/x-3dmf"},
{ "a","application/octet-stream"},
{ "aab","application/x-authorware-bin"},
{ "aam","application/x-authorware-map"},
{ "aas","application/x-authorware-seg"},
{ "abc","text/vnd.abc"},
{ "acgi","text/html"},
{ "afl","video/animaflex"},
{ "ai","application/postscript"},
{ "aif","audio/x-aiff"},
{ "aifc","audio/x-aiff"},
{ "aiff","audio/x-aiff"},
{ "aim","application/x-aim"},
{ "aip","text/x-audiosoft-intra"},
{ "ani","application/x-navi-animation"},
{ "aos","application/x-nokia-9000-communicator-add-on-software"},
{ "aps","application/mime"},
{ "arc","application/octet-stream"},
{ "arj","application/octet-stream"},
{ "art","image/x-jg"},
{ "asf","video/x-ms-asf"},
{ "asm","text/x-asm"},
{ "asp","text/asp"},
{ "asx","video/x-ms-asf-plugin"},
{ "au","audio/x-au"},
{ "avi","video/x-msvideo"},
{ "avs","video/avs-video"},
{ "bcpio","application/x-bcpio"},
{ "bin","application/x-macbinary"},
{ "bm","image/bmp"},
{ "bmp","image/x-windows-bmp"},
{ "boo","application/book"},
{ "book","application/book"},
{ "boz","application/x-bzip2"},
{ "bsh","application/x-bsh"},
{ "bz","application/x-bzip"},
{ "bz2","application/x-bzip2"},
{ "c","text/x-c"},
{ "c++","text/plain"},
{ "cat","application/vnd.ms-pki.seccat"},
{ "cc","text/x-c"},
{ "ccad","application/clariscad"},
{ "cco","application/x-cocoa"},
{ "cdf","application/x-netcdf"},
{ "cer","application/x-x509-ca-cert"},
{ "cha","application/x-chat"},
{ "chat","application/x-chat"},
{ "class","application/x-java-class"},
{ "com","text/plain"},
{ "conf","text/plain"},
{ "cpio","application/x-cpio"},
{ "cpp","text/x-c"},
{ "cpt","application/x-cpt"},
{ "crl","application/pkix-crl"},
{ "crt","application/x-x509-user-cert"},
{ "csh","text/x-script.csh"},
{ "css","text/css"},
{ "cxx","text/plain"},
{ "dcr","application/x-director"},
{ "deepv","application/x-deepv"},
{ "def","text/plain"},
{ "der","application/x-x509-ca-cert"},
{ "dif","video/x-dv"},
{ "dir","application/x-director"},
{ "dl","video/x-dl"},
{ "doc","application/msword"},
{ "dot","application/msword"},
{ "dp","application/commonground"},
{ "drw","application/drafting"},
{ "dump","application/octet-stream"},
{ "dv","video/x-dv"},
{ "dvi","application/x-dvi"},
{ "dwf","model/vnd.dwf"},
{ "dwg","image/x-dwg"},
{ "dxf","image/x-dwg"},
{ "dxr","application/x-director"},
{ "el","text/x-script.elisp"},
{ "elc","application/x-elc"},
{ "env","application/x-envoy"},
{ "eps","application/postscript"},
{ "es","application/x-esrehber"},
{ "etx","text/x-setext"},
{ "evy","application/x-envoy"},
{ "exe","application/octet-stream"},
{ "f","text/x-fortran"},
{ "f77","text/x-fortran"},
{ "f90","text/x-fortran"},
{ "fdf","application/vnd.fdf"},
{ "fif","image/fif"},
{ "fli","video/x-fli"},
{ "flo","image/florian"},
{ "flx","text/vnd.fmi.flexstor"},
{ "fmf","video/x-atomic3d-feature"},
{ "for","text/x-fortran"},
{ "fpx","image/vnd.net-fpx"},
{ "frl","application/freeloader"},
{ "funk","audio/make"},
{ "g","text/plain"},
{ "g3","image/g3fax"},
{ "gif","image/gif"},
{ "gl","video/x-gl"},
{ "gsd","audio/x-gsm"},
{ "gsm","audio/x-gsm"},
{ "gsp","application/x-gsp"},
{ "gss","application/x-gss"},
{ "gtar","application/x-gtar"},
{ "gz","application/x-gzip"},
{ "gzip","multipart/x-gzip"},
{ "h","text/x-h"},
{ "hdf","application/x-hdf"},
{ "help","application/x-helpfile"},
{ "hgl","application/vnd.hp-hpgl"},
{ "hh","text/x-h"},
{ "hlb","text/x-script"},
{ "hlp","application/x-winhelp"},
{ "hpg","application/vnd.hp-hpgl"},
{ "hpgl","application/vnd.hp-hpgl"},
{ "hqx","application/x-mac-binhex40"},
{ "hta","application/hta"},
{ "htc","text/x-component"},
{ "htm","text/html"},
{ "html","text/html"},
{ "htmls","text/html"},
{ "htt","text/webviewhtml"},
{ "htx","text/html"},
{ "ice","x-conference/x-cooltalk"},
{ "ico","image/x-icon"},
{ "idc","text/plain"},
{ "ief","image/ief"},
{ "iefs","image/ief"},
{ "iges","model/iges"},
{ "igs","model/iges"},
{ "ima","application/x-ima"},
{ "imap","application/x-httpd-imap"},
{ "inf","application/inf"},
{ "ins","application/x-internett-signup"},
{ "ip","application/x-ip2"},
{ "isu","video/x-isvideo"},
{ "it","audio/it"},
{ "iv","application/x-inventor"},
{ "ivr","i-world/i-vrml"},
{ "ivy","application/x-livescreen"},
{ "jam","audio/x-jam"},
{ "jav","text/x-java-source"},
{ "java","text/x-java-source"},
{ "jcm","application/x-java-commerce"},
{ "jfif","image/pjpeg"},
{ "jfif-tbnl","image/jpeg"},
{ "jpe","image/pjpeg"},
{ "jpeg","image/pjpeg"},
{ "jpg","image/pjpeg"},
{ "jps","image/x-jps"},
{ "js","text/ecmascript"},
{ "jut","image/jutvision"},
{ "kar","music/x-karaoke"},
{ "ksh","text/x-script.ksh"},
{ "la","audio/x-nspaudio"},
{ "lam","audio/x-liveaudio"},
{ "latex","application/x-latex"},
{ "lha","application/x-lha"},
{ "lhx","application/octet-stream"},
{ "list","text/plain"},
{ "lma","audio/x-nspaudio"},
{ "log","text/plain"},
{ "lsp","text/x-script.lisp"},
{ "lst","text/plain"},
{ "lsx","text/x-la-asf"},
{ "ltx","application/x-latex"},
{ "lzh","application/x-lzh"},
{ "lzx","application/x-lzx"},
{ "m","text/x-m"},
{ "m1v","video/mpeg"},
{ "m2a","audio/mpeg"},
{ "m2v","video/mpeg"},
{ "m3u","audio/x-mpequrl"},
{ "man","application/x-troff-man"},
{ "map","application/x-navimap"},
{ "mar","text/plain"},
{ "mbd","application/mbedlet"},
{ "mc$","application/x-magic-cap-package-1.0"},
{ "mcd","application/x-mathcad"},
{ "mcf","text/mcf"},
{ "mcp","application/netmc"},
{ "me","application/x-troff-me"},
{ "mht","message/rfc822"},
{ "mhtml","message/rfc822"},
{ "mid","x-music/x-midi"},
{ "midi","x-music/x-midi"},
{ "mif","application/x-mif"},
{ "mime","www/mime"},
{ "mjf","audio/x-vnd.audioexplosion.mjuicemediafile"},
{ "mjpg","video/x-motion-jpeg"},
{ "mm","application/x-meme"},
{ "mme","application/base64"},
{ "mod","audio/x-mod"},
{ "moov","video/quicktime"},
{ "mov","video/quicktime"},
{ "movie","video/x-sgi-movie"},
{ "mp2","video/x-mpeq2a"},
{ "mp3","video/x-mpeg"},
{ "mpa","video/mpeg"},
{ "mpc","application/x-project"},
{ "mpe","video/mpeg"},
{ "mpeg","video/mpeg"},
{ "mpg","video/mpeg"},
{ "mpga","audio/mpeg"},
{ "mpp","application/vnd.ms-project"},
{ "mpt","application/x-project"},
{ "mpv","application/x-project"},
{ "mpx","application/x-project"},
{ "mrc","application/marc"},
{ "ms","application/x-troff-ms"},
{ "mv","video/x-sgi-movie"},
{ "my","audio/make"},
{ "mzz","application/x-vnd.audioexplosion.mzz"},
{ "nap","image/naplps"},
{ "naplps","image/naplps"},
{ "nc","application/x-netcdf"},
{ "ncm","application/vnd.nokia.configuration-message"},
{ "nif","image/x-niff"},
{ "niff","image/x-niff"},
{ "nix","application/x-mix-transfer"},
{ "nsc","application/x-conference"},
{ "nvd","application/x-navidoc"},
{ "o","application/octet-stream"},
{ "oda","application/oda"},
{ "omc","application/x-omc"},
{ "omcd","application/x-omcdatamaker"},
{ "omcr","application/x-omcregerator"},
{ "p","text/x-pascal"},
{ "p10","application/x-pkcs10"},
{ "p12","application/x-pkcs12"},
{ "p7a","application/x-pkcs7-signature"},
{ "p7c","application/x-pkcs7-mime"},
{ "p7m","application/x-pkcs7-mime"},
{ "p7r","application/x-pkcs7-certreqresp"},
{ "p7s","application/pkcs7-signature"},
{ "part","application/pro_eng"},
{ "pas","text/pascal"},
{ "pbm","image/x-portable-bitmap"},
{ "pcl","application/x-pcl"},
{ "pct","image/x-pict"},
{ "pcx","image/x-pcx"},
{ "pdb","chemical/x-pdb"},
{ "pdf","application/pdf"},
{ "pfunk","audio/make.my.funk"},
{ "pgm","image/x-portable-greymap"},
{ "pic","image/pict"},
{ "pict","image/pict"},
{ "pkg","application/x-newton-compatible-pkg"},
{ "pko","application/vnd.ms-pki.pko"},
{ "pl","text/x-script.perl"},
{ "plx","application/x-pixclscript"},
{ "pm","text/x-script.perl-module"},
{ "pm4","application/x-pagemaker"},
{ "pm5","application/x-pagemaker"},
{ "png","image/png"},
{ "pnm","image/x-portable-anymap"},
{ "pot","application/vnd.ms-powerpoint"},
{ "pov","model/x-pov"},
{ "ppa","application/vnd.ms-powerpoint"},
{ "ppm","image/x-portable-pixmap"},
{ "pps","application/vnd.ms-powerpoint"},
{ "ppt","application/x-mspowerpoint"},
{ "ppz","application/mspowerpoint"},
{ "pre","application/x-freelance"},
{ "prt","application/pro_eng"},
{ "ps","application/postscript"},
{ "psd","application/octet-stream"},
{ "pvu","paleovu/x-pv"},
{ "pwz","application/vnd.ms-powerpoint"},
{ "py","text/x-script.phyton"},
{ "pyc","application/x-bytecode.python"},
{ "qcp","audio/vnd.qcelp"},
{ "qd3","x-world/x-3dmf"},
{ "qd3d","x-world/x-3dmf"},
{ "qif","image/x-quicktime"},
{ "qt","video/quicktime"},
{ "qtc","video/x-qtc"},
{ "qti","image/x-quicktime"},
{ "qtif","image/x-quicktime"},
{ "ra","audio/x-realaudio"},
{ "ram","audio/x-pn-realaudio"},
{ "ras","image/x-cmu-raster"},
{ "rast","image/cmu-raster"},
{ "rexx","text/x-script.rexx"},
{ "rf","image/vnd.rn-realflash"},
{ "rgb","image/x-rgb"},
{ "rm","audio/x-pn-realaudio"},
{ "rmi","audio/mid"},
{ "rmm","audio/x-pn-realaudio"},
{ "rmp","audio/x-pn-realaudio-plugin"},
{ "rng","application/vnd.nokia.ringing-tone"},
{ "rnx","application/vnd.rn-realplayer"},
{ "roff","application/x-troff"},
{ "rp","image/vnd.rn-realpix"},
{ "rpm","audio/x-pn-realaudio-plugin"},
{ "rt","text/vnd.rn-realtext"},
{ "rtf","text/richtext"},
{ "rtx","text/richtext"},
{ "rv","video/vnd.rn-realvideo"},
{ "s","text/x-asm"},
{ "s3m","audio/s3m"},
{ "saveme","application/octet-stream"},
{ "sbk","application/x-tbook"},
{ "scm","video/x-scm"},
{ "sdml","text/plain"},
{ "sdp","application/x-sdp"},
{ "sdr","application/sounder"},
{ "sea","application/x-sea"},
{ "set","application/set"},
{ "sgm","text/x-sgml"},
{ "sgml","text/x-sgml"},
{ "sh","text/x-script.sh"},
{ "shar","application/x-shar"},
{ "shtml","text/x-server-parsed-html"},
{ "sid","audio/x-psid"},
{ "sit","application/x-stuffit"},
{ "skd","application/x-koan"},
{ "skm","application/x-koan"},
{ "skp","application/x-koan"},
{ "skt","application/x-koan"},
{ "sl","application/x-seelogo"},
{ "smi","application/smil"},
{ "smil","application/smil"},
{ "snd","audio/x-adpcm"},
{ "sol","application/solids"},
{ "spc","text/x-speech"},
{ "spl","application/futuresplash"},
{ "spr","application/x-sprite"},
{ "sprite","application/x-sprite"},
{ "src","application/x-wais-source"},
{ "ssi","text/x-server-parsed-html"},
{ "ssm","application/streamingmedia"},
{ "sst","application/vnd.ms-pki.certstore"},
{ "step","application/step"},
{ "stl","application/x-navistyle"},
{ "stp","application/step"},
{ "sv4cpio","application/x-sv4cpio"},
{ "sv4crc","application/x-sv4crc"},
{ "svf","image/x-dwg"},
{ "svr","x-world/x-svr"},
{ "swf","application/x-shockwave-flash"},
{ "t","application/x-troff"},
{ "talk","text/x-speech"},
{ "tar","application/x-tar"},
{ "tbk","application/x-tbook"},
{ "tcl","text/x-script.tcl"},
{ "tcsh","text/x-script.tcsh"},
{ "tex","application/x-tex"},
{ "texi","application/x-texinfo"},
{ "texinfo","application/x-texinfo"},
{ "text","text/plain"},
{ "tgz","application/x-compressed"},
{ "tif","image/x-tiff"},
{ "tiff","image/x-tiff"},
{ "tr","application/x-troff"},
{ "tsi","audio/tsp-audio"},
{ "tsp","audio/tsplayer"},
{ "tsv","text/tab-separated-values"},
{ "turbot","image/florian"},
{ "txt","text/plain"},
{ "uil","text/x-uil"},
{ "uni","text/uri-list"},
{ "unis","text/uri-list"},
{ "unv","application/i-deas"},
{ "uri","text/uri-list"},
{ "uris","text/uri-list"},
{ "ustar","multipart/x-ustar"},
{ "uu","text/x-uuencode"},
{ "uue","text/x-uuencode"},
{ "vcd","application/x-cdlink"},
{ "vcs","text/x-vcalendar"},
{ "vda","application/vda"},
{ "vdo","video/vdo"},
{ "vew","application/groupwise"},
{ "viv","video/vnd.vivo"},
{ "vivo","video/vnd.vivo"},
{ "vmd","application/vocaltec-media-desc"},
{ "vmf","application/vocaltec-media-file"},
{ "voc","audio/x-voc"},
{ "vos","video/vosaic"},
{ "vox","audio/voxware"},
{ "vqe","audio/x-twinvq-plugin"},
{ "vqf","audio/x-twinvq"},
{ "vql","audio/x-twinvq-plugin"},
{ "vrml","x-world/x-vrml"},
{ "vrt","x-world/x-vrt"},
{ "vsd","application/x-visio"},
{ "vst","application/x-visio"},
{ "vsw","application/x-visio"},
{ "w60","application/wordperfect6.0"},
{ "w61","application/wordperfect6.1"},
{ "w6w","application/msword"},
{ "wav","audio/x-wav"},
{ "wb1","application/x-qpro"},
{ "wbmp","image/vnd.wap.wbmp"},
{ "web","application/vnd.xara"},
{ "wiz","application/msword"},
{ "wk1","application/x-123"},
{ "wmf","windows/metafile"},
{ "wml","text/vnd.wap.wml"},
{ "wmlc","application/vnd.wap.wmlc"},
{ "wmls","text/vnd.wap.wmlscript"},
{ "wmlsc","application/vnd.wap.wmlscriptc"},
{ "word","application/msword"},
{ "wp","application/wordperfect"},
{ "wp5","application/wordperfect6.0"},
{ "wp6","application/wordperfect"},
{ "wpd","application/x-wpwin"},
{ "wq1","application/x-lotus"},
{ "wri","application/x-wri"},
{ "wrl","x-world/x-vrml"},
{ "wrz","x-world/x-vrml"},
{ "wsc","text/scriplet"},
{ "wsrc","application/x-wais-source"},
{ "wtk","application/x-wintalk"},
{ "xbm","image/xbm"},
{ "xdr","video/x-amt-demorun"},
{ "xgz","xgl/drawing"},
{ "xif","image/vnd.xiff"},
{ "xl","application/excel"},
{ "xla","application/x-msexcel"},
{ "xlb","application/x-excel"},
{ "xlc","application/x-excel"},
{ "xld","application/x-excel"},
{ "xlk","application/x-excel"},
{ "xll","application/x-excel"},
{ "xlm","application/x-excel"},
{ "xls","application/x-msexcel"},
{ "xlt","application/x-excel"},
{ "xlv","application/x-excel"},
{ "xlw","application/x-msexcel"},
{ "xm","audio/xm"},
{ "xml","text/xml"},
{ "xmz","xgl/movie"},
{ "xpix","application/x-vnd.ls-xpix"},
{ "xpm","image/xpm"},
{ "x-png","image/png"},
{ "xsr","video/x-amt-showrun"},
{ "xwd","image/x-xwindowdump"},
{ "xyz","chemical/x-pdb"},
{ "z","application/x-compressed"},
{ "zip","multipart/x-zip"},
{ "zoo","application/octet-stream"},
{ "zsh","text/x-script.zsh"}
};


return MIMELIST;


}
