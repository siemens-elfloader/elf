
#ifndef _NNTP_HPP_
#define _NNTP_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwNNTPActions {
  nntpIdle,
  nntpConnect,
  nntpDisconnect,
  nntpListGroups,
  nntpListNewGroups,
  nntpGroupOverview,
  nntpGetArticle,
  nntpGetArticleHeaders,
  nntpGetArticleBody,
  nntpPostArticle,
  nntpResetHeaders,
  nntpGroupSearch
};
typedef TFIREWALLTYPES TipwNNTPFirewallTypes;




typedef void __fastcall (__closure* TipwNNTPEndTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwNNTPErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwNNTPGroupListEvent)(System::TObject* Sender,
                                    AnsiString& Group,
                                    long FirstArticle,
                                    long LastArticle,
                                    bool CanPost);
typedef void __fastcall (__closure* TipwNNTPGroupOverviewEvent)(System::TObject* Sender,
                                    long ArticleNumber,
                                    AnsiString& Subject,
                                    AnsiString& From,
                                    AnsiString& ArticleDate,
                                    AnsiString& MessageId,
                                    AnsiString& References,
                                    long ArticleSize,
                                    long ArticleLines,
                                    AnsiString& OtherHeaders);
typedef void __fastcall (__closure* TipwNNTPGroupSearchEvent)(System::TObject* Sender,
                                    long ArticleNumber,
                                    AnsiString& Header);
typedef void __fastcall (__closure* TipwNNTPHeaderEvent)(System::TObject* Sender,
                                    AnsiString& Field,
                                    AnsiString& Value);
typedef void __fastcall (__closure* TipwNNTPPITrailEvent)(System::TObject* Sender,
                                    int Direction,
                                    AnsiString& Message);
typedef void __fastcall (__closure* TipwNNTPStartTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwNNTPTransferEvent)(System::TObject* Sender,
                                    long BytesTransferred,
                                    char * Text, USHORT lenText,
                                    bool EOL);


class PACKAGE TipwNNTP : public IPWCore
{
private:
  LONG reserved;
  TipwNNTPEndTransferEvent FOnEndTransfer;
  TipwNNTPErrorEvent FOnError;
  TipwNNTPGroupListEvent FOnGroupList;
  TipwNNTPGroupOverviewEvent FOnGroupOverview;
  TipwNNTPGroupSearchEvent FOnGroupSearch;
  TipwNNTPHeaderEvent FOnHeader;
  TipwNNTPPITrailEvent FOnPITrail;
  TipwNNTPStartTransferEvent FOnStartTransfer;
  TipwNNTPTransferEvent FOnTransfer;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //The full text of the article (without the headers).  //
  AnsiString __fastcall FArticleText();
  void __fastcall FSetArticleText(AnsiString lpszArticleText);

  //A file name which contents to append to ArticleText when posting articles.  //
  AnsiString __fastcall FAttachedFile();
  void __fastcall FSetAttachedFile(AnsiString lpszAttachedFile);

  //The date (format YYMMDD HHMMSS) since when to check for creation of new groups.  //
  AnsiString __fastcall FCheckDate();
  void __fastcall FSetCheckDate(AnsiString lpszCheckDate);

  //Can be used to send additional commands directly to the NNTP server.  //

  void __fastcall FSetCommand(AnsiString lpszCommand);

  //Shows whether the component is connected.  //
  bool __fastcall FConnected();


  //Used to send other data to firewall.  //
  AnsiString __fastcall FFirewallData();
  void __fastcall FSetFirewallData(AnsiString lpFirewallData);
  void __fastcall SetFirewallData(char *lpFirewallData, USHORT lenFirewallData);


  //The email address of the author (for posting articles).  //
  AnsiString __fastcall FFrom();
  void __fastcall FSetFrom(AnsiString lpszFrom);

  //Maximum length for headers to avoid line folding (default 80).  //
  USHORT __fastcall FMaxHeaderLength();
  void __fastcall FSetMaxHeaderLength(USHORT usMaxHeaderLength);

  //The maximum number of message lines beside headers to retrieve.  //
  USHORT __fastcall FMaxLines();
  void __fastcall FSetMaxLines(USHORT usMaxLines);

  //A comma separated list of newsgroups where to post the article.  //
  AnsiString __fastcall FNewsgroups();
  void __fastcall FSetNewsgroups(AnsiString lpszNewsgroups);

  //The server port for NNTP (default 119).  //
  USHORT __fastcall FNewsPort();
  void __fastcall FSetNewsPort(USHORT usNewsPort);

  //The organization of the author (for posting articles).  //
  AnsiString __fastcall FOrganization();
  void __fastcall FSetOrganization(AnsiString lpszOrganization);

  //An RFC850 compliant string consisting of extra headers (for posting articles).  //
  AnsiString __fastcall FOtherHeaders();
  void __fastcall FSetOtherHeaders(AnsiString lpszOtherHeaders);

  //A range for the nntpGroupOverview action (first-last).  //
  AnsiString __fastcall FOverviewRange();
  void __fastcall FSetOverviewRange(AnsiString lpszOverviewRange);

  //Articles the posted article follows up to.  //
  AnsiString __fastcall FReferences();
  void __fastcall FSetReferences(AnsiString lpszReferences);

  //The address to reply to (for posting articles).  //
  AnsiString __fastcall FReplyTo();
  void __fastcall FSetReplyTo(AnsiString lpszReplyTo);

  //A header for the nntpGroupSearch action.  //
  AnsiString __fastcall FSearchHeader();
  void __fastcall FSetSearchHeader(AnsiString lpszSearchHeader);

  //A search pattern for the nntpGroupSearch action.  //
  AnsiString __fastcall FSearchPattern();
  void __fastcall FSetSearchPattern(AnsiString lpszSearchPattern);

  //A range for the nntpGroupSearch action (first-last).  //
  AnsiString __fastcall FSearchRange();
  void __fastcall FSetSearchRange(AnsiString lpszSearchRange);

  //The handle of the main socket used by the component.  //
  long __fastcall FSocketHandle();


  //The article subject (for posted articles).  //
  AnsiString __fastcall FSubject();
  void __fastcall FSetSubject(AnsiString lpszSubject);

  //Size in bytes of the largest UDP datagram that can be sent or received (Windows only).  //
  USHORT __fastcall FWinsockMaxDatagramSize();


  //Maximum number of sockets available to a single process (Windows only).  //
  USHORT __fastcall FWinsockMaxSockets();


  //The path to the Winsock DLL used (Windows only).  //
  AnsiString __fastcall FWinsockPath();
  void __fastcall FSetWinsockPath(AnsiString lpszWinsockPath);



  //Design-Time Properties
  TipwNNTPActions __fastcall FAction();
  void __fastcall FSetAction(TipwNNTPActions iAction);

  long __fastcall FArticleCount();


  AnsiString __fastcall FArticleHeaders();












  AnsiString __fastcall FCurrentArticle();
  void __fastcall FSetCurrentArticle(AnsiString lpszCurrentArticle);

  AnsiString __fastcall FCurrentGroup();
  void __fastcall FSetCurrentGroup(AnsiString lpszCurrentGroup);



  AnsiString __fastcall FFirewallHost();
  void __fastcall FSetFirewallHost(AnsiString lpszFirewallHost);

  AnsiString __fastcall FFirewallPassword();
  void __fastcall FSetFirewallPassword(AnsiString lpszFirewallPassword);

  USHORT __fastcall FFirewallPort();
  void __fastcall FSetFirewallPort(USHORT usFirewallPort);

  TipwNNTPFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipwNNTPFirewallTypes iFirewallType);

  AnsiString __fastcall FFirewallUser();
  void __fastcall FSetFirewallUser(AnsiString lpszFirewallUser);

  long __fastcall FFirstArticle();




  long __fastcall FLastArticle();


  AnsiString __fastcall FLastReply();


  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);









  AnsiString __fastcall FNewsServer();
  void __fastcall FSetNewsServer(AnsiString lpszNewsServer);







  AnsiString __fastcall FPassword();
  void __fastcall FSetPassword(AnsiString lpszPassword);















  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);

  AnsiString __fastcall FUser();
  void __fastcall FSetUser(AnsiString lpszUser);

  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwNNTP(TComponent* Owner);
  virtual __fastcall TipwNNTP(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_25);
  virtual __fastcall ~TipwNNTP();


  //Fired when the article text completes transferring.  //
  virtual void FireEndTransfer();
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired while group data transfers (during group listings).  //
  virtual void FireGroupList(char* Group, long FirstArticle, long LastArticle, bool CanPost);
  //Fired for each line of article overview data (during group overviews).  //
  virtual void FireGroupOverview(long ArticleNumber, char* Subject, char* From, char* ArticleDate, char* MessageId, char* References, long ArticleSize, long ArticleLines, char* OtherHeaders);
  //Fired for each line of group search data (during group searches).  //
  virtual void FireGroupSearch(long ArticleNumber, char* Header);
  //Fired for every article header being retrieved during article retrieval.  //
  virtual void FireHeader(char* Field, char* Value);
  //Traces the commands sent to the news server, and the respective replies.  //
  virtual void FirePITrail(int Direction, char* Message);
  //Fired when the article text starts transferring.  //
  virtual void FireStartTransfer();
  //Fired while the article text gets transferred (to or from the NewsServer ).  //
  virtual void FireTransfer(long BytesTransferred, char* Text, USHORT lenText, bool EOL);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };







  __property AnsiString ArticleText = {
               read=FArticleText,
               write=FSetArticleText               };

  __property AnsiString AttachedFile = {
               read=FAttachedFile,
               write=FSetAttachedFile               };

  __property AnsiString CheckDate = {
               read=FCheckDate,
               write=FSetCheckDate               };

  __property AnsiString Command = {

               write=FSetCommand               };

  __property bool Connected = {
               read=FConnected
               };





  __property AnsiString FirewallData = {
               read=FFirewallData,
               write=FSetFirewallData               };













  __property AnsiString From = {
               read=FFrom,
               write=FSetFrom               };







  __property USHORT MaxHeaderLength = {
               read=FMaxHeaderLength,
               write=FSetMaxHeaderLength               };

  __property USHORT MaxLines = {
               read=FMaxLines,
               write=FSetMaxLines               };

  __property AnsiString Newsgroups = {
               read=FNewsgroups,
               write=FSetNewsgroups               };

  __property USHORT NewsPort = {
               read=FNewsPort,
               write=FSetNewsPort               };



  __property AnsiString Organization = {
               read=FOrganization,
               write=FSetOrganization               };

  __property AnsiString OtherHeaders = {
               read=FOtherHeaders,
               write=FSetOtherHeaders               };

  __property AnsiString OverviewRange = {
               read=FOverviewRange,
               write=FSetOverviewRange               };



  __property AnsiString References = {
               read=FReferences,
               write=FSetReferences               };

  __property AnsiString ReplyTo = {
               read=FReplyTo,
               write=FSetReplyTo               };

  __property AnsiString SearchHeader = {
               read=FSearchHeader,
               write=FSetSearchHeader               };

  __property AnsiString SearchPattern = {
               read=FSearchPattern,
               write=FSetSearchPattern               };

  __property AnsiString SearchRange = {
               read=FSearchRange,
               write=FSetSearchRange               };

  __property long SocketHandle = {
               read=FSocketHandle
               };

  __property AnsiString Subject = {
               read=FSubject,
               write=FSetSubject               };









  __property USHORT WinsockMaxDatagramSize = {
               read=FWinsockMaxDatagramSize
               };

  __property USHORT WinsockMaxSockets = {
               read=FWinsockMaxSockets
               };

  __property AnsiString WinsockPath = {
               read=FWinsockPath,
               write=FSetWinsockPath               };





  //METHODS
    void __fastcall Connect();
    void __fastcall Disconnect();
    void __fastcall DoEvents();
    void __fastcall FetchArticle();
    void __fastcall FetchArticleBody();
    void __fastcall FetchArticleHeaders();
    void __fastcall GroupOverview();
    void __fastcall GroupSearch();
    void __fastcall Interrupt();
    void __fastcall ListGroups();
    void __fastcall ListNewGroups();
    void __fastcall PostArticle();
    void __fastcall ResetHeaders();




__published:

  //PROPERTIES
    __property TipwNNTPActions Action = {
                    read=FAction,
                    write=FSetAction,
                    stored=false

                   };
    __property long ArticleCount = {
                    read=FArticleCount,
                    write=SetDummylong,
                    stored=false

                   };
    __property AnsiString ArticleHeaders = {
                    read=FArticleHeaders,
                    write=SetDummyAnsiString,
                    stored=false

                   };





    __property AnsiString CurrentArticle = {
                    read=FCurrentArticle,
                    write=FSetCurrentArticle,
                    
                   };
    __property AnsiString CurrentGroup = {
                    read=FCurrentGroup,
                    write=FSetCurrentGroup,
                    
                   };

    __property AnsiString FirewallHost = {
                    read=FFirewallHost,
                    write=FSetFirewallHost,
                    
                   };
    __property AnsiString FirewallPassword = {
                    read=FFirewallPassword,
                    write=FSetFirewallPassword,
                    
                   };
    __property USHORT FirewallPort = {
                    read=FFirewallPort,
                    write=FSetFirewallPort,
                    default=0
                   };
    __property TipwNNTPFirewallTypes FirewallType = {
                    read=FFirewallType,
                    write=FSetFirewallType,
                    default=fwNone
                   };
    __property AnsiString FirewallUser = {
                    read=FFirewallUser,
                    write=FSetFirewallUser,
                    
                   };
    __property long FirstArticle = {
                    read=FFirstArticle,
                    write=SetDummylong,
                    stored=false

                   };

    __property long LastArticle = {
                    read=FLastArticle,
                    write=SetDummylong,
                    stored=false

                   };
    __property AnsiString LastReply = {
                    read=FLastReply,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString LocalHost = {
                    read=FLocalHost,
                    write=FSetLocalHost,
                    stored=false

                   };




    __property AnsiString NewsServer = {
                    read=FNewsServer,
                    write=FSetNewsServer,
                    
                   };



    __property AnsiString Password = {
                    read=FPassword,
                    write=FSetPassword,
                    
                   };







    __property int Timeout = {
                    read=FTimeout,
                    write=FSetTimeout,
                    default=0
                   };
    __property AnsiString User = {
                    read=FUser,
                    write=FSetUser,
                    
                   };
    __property AnsiString WinsockInfo = {
                    read=FWinsockInfo,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property bool WinsockLoaded = {
                    read=FWinsockLoaded,
                    write=FSetWinsockLoaded,
                    default=true
                   };



    __property AnsiString WinsockStatus = {
                    read=FWinsockStatus,
                    write=SetDummyAnsiString,
                    stored=false

                   };


  //EVENTS
    //Fired when the article text completes transferring.
    __property TipwNNTPEndTransferEvent OnEndTransfer = {read=FOnEndTransfer, write=FOnEndTransfer};
    //Information about errors during data delivery.
    __property TipwNNTPErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired while group data transfers (during group listings).
    __property TipwNNTPGroupListEvent OnGroupList = {read=FOnGroupList, write=FOnGroupList};
    //Fired for each line of article overview data (during group overviews).
    __property TipwNNTPGroupOverviewEvent OnGroupOverview = {read=FOnGroupOverview, write=FOnGroupOverview};
    //Fired for each line of group search data (during group searches).
    __property TipwNNTPGroupSearchEvent OnGroupSearch = {read=FOnGroupSearch, write=FOnGroupSearch};
    //Fired for every article header being retrieved during article retrieval.
    __property TipwNNTPHeaderEvent OnHeader = {read=FOnHeader, write=FOnHeader};
    //Traces the commands sent to the news server, and the respective replies.
    __property TipwNNTPPITrailEvent OnPITrail = {read=FOnPITrail, write=FOnPITrail};
    //Fired when the article text starts transferring.
    __property TipwNNTPStartTransferEvent OnStartTransfer = {read=FOnStartTransfer, write=FOnStartTransfer};
    //Fired while the article text gets transferred (to or from the NewsServer ).
    __property TipwNNTPTransferEvent OnTransfer = {read=FOnTransfer, write=FOnTransfer};


}; //end class TipwNNTP

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _NNTP_HPP_

