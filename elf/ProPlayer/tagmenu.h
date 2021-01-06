#ifndef _TAGMENU_H_
#define _TAGMENU_H_

/* ID3v1 
  Byte 1-3 = ID "TAG" 
  Byte 4-33 = Title 
  Byte 34-63 = Artist 
  Byte 64-93 = Album 
  Byte 94-97 = Year 
  Byte 98-127 = Comment 
  Byte 128 = Genre 
*/

typedef struct
{   char ID[3]; 
    char Title[30]; 
    char Artist[30]; 
    char Album[30]; 
    char Year[4]; 
    char Comment[30]; 
    char Genre[1]; 
}TID3TagV1;

/* ID3v1.1
  Byte 1-3 = ID "TAG" 
  Byte 4-33 = Title 
  Byte 34-63 = Artist 
  Byte 64-93 = Album 
  Byte 94-97 = Year 
  Byte 98-125 = Comment 
  Byte 126 = unused
  Byte 127 = Track
  Byte 128 = Genre 
*/
typedef struct
{   char ID[3]; 
    char Title[30]; 
    char Artist[30]; 
    char Album[30]; 
    char Year[4]; 
    char Comment[28];
    char Unused[1];
    unsigned char Track;
    unsigned char Genre; 
}TID3TagV1_1;


static const char * const Genres[148]=
{  //0-79
   "Blues","Classic Rock","Country","Dance","Disco",
   "Funk","Grunge","Hip- Hop","Jazz","Metal",
   "New Age","Oldies","Other","Pop","R&B", 
   "Rap","Reggae","Rock","Techno","Industrial",
   "Alternative","Ska","Death Metal","Pranks","Soundtrack",
   "Euro-Techno","Ambient","Trip-Hop","Vocal","Jazz+Funk",
   "Fusion","Trance","Classical","Instrumental","Acid",
   "House","Game","Sound Clip","Gospel","Noise", 
   "Alternative Rock","Bass","Soul","Punk","Space",
   "Meditative","Instrumental Pop","Instrumental Rock","Ethnic","Gothic",
   "Darkwave","Techno-Industrial","Electronic","Pop-Folk","Eurodance",
   "Dream","Southern Rock","Comedy","Cult","Gangsta",
   "Top 40","Christian Rap","Pop/Funk","Jungle","Native US",
   "Cabaret","New Wave","Psychadelic","Rave","Showtunes",
   "Trailer","Lo-Fi","Tribal","Acid Punk", "Acid Jazz",
   "Polka","Retro","Musical","Rock & Roll","Hard Rock",
   //80-125
   "Folk","Folk-Rock","National Folk","Swing","Fast Fusion",
   "Bebob","Latin","Revival","Celtic","Bluegrass",
   "Avantgarde","Gothic Rock","Progressive Rock","Psychedelic Rock","Symphonic Rock",
   "Slow Rock","Big Band","Chorus","Easy Listening","Acoustic",
   "Humour","Speech","Chanson","Opera","Chamber Music",
   "Sonata","Symphony","Booty Bass","Primus","Porn Groove",
   "Satire","Slow Jam","Club","Tango","Samba",
   "Folklore","Ballad","Power Ballad","Rhytmic Soul","Freestyle",
   "Duet","Punk Rock","Drum Solo","Acapella","Euro-House",
   "Dance Hall",
    //126-147
    "Goa","Drum & Bass","Club-House", 
    "Hardcore","Terror","Indie","BritPop","Negerpunk","Polsk Punk","Beat", 
    "Christian Gangsta","Heavy Metal","Black Metal","Crossover","Contemporary C", 
    "Christian Rock","Merengue","Salsa","Thrash Metal","Anime","JPop","SynthPop"
};

int CreateTagMenu(void);

#endif
