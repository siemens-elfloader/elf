/*
    SieNatJabber Project
    Константы, множества протокола XMPP

*/
#ifndef _JABBER_H_
  #define _JABBER_H_
// Error code
#define JABBER_ERROR_REDIRECT				302
#define JABBER_ERROR_BAD_REQUEST			400
#define JABBER_ERROR_UNAUTHORIZED			401
#define JABBER_ERROR_PAYMENT_REQUIRED		        402
#define JABBER_ERROR_FORBIDDEN				403
#define JABBER_ERROR_NOT_FOUND				404
#define JABBER_ERROR_NOT_ALLOWED			405
#define JABBER_ERROR_NOT_ACCEPTABLE			406
#define JABBER_ERROR_REGISTRATION_REQUIRED	        407
#define JABBER_ERROR_REQUEST_TIMEOUT		        408
#define JABBER_ERROR_CONFLICT				409
#define JABBER_ERROR_INTERNAL_SERVER_ERROR	500
#define JABBER_ERROR_NOT_IMPLEMENTED		501
#define JABBER_ERROR_REMOTE_SERVER_ERROR	502
#define JABBER_ERROR_SERVICE_UNAVAILABLE	503
#define JABBER_ERROR_REMOTE_SERVER_TIMEOUT	504

#define MUCST_BANNED  "301"
#define MUCST_R_BAN  "%s was BANNED! "

#define MUCST_CHNICK  "303"
#define MUCST_R_CHNICK  "%s is now known as %s"

#define MUCST_KICKED  "307"
#define MUCST_R_KICK  "%s was kicked! "

#define MUCST_KICKED_MEMB_ONLY  "322"
#define MUCST_R_KICK_MEMB_ONLY  "%s was kicked, because room became member-only!"


#define IQTYPE_GET "get"
#define IQTYPE_SET "set"
#define IQTYPE_RES "result"
#define IQTYPE_ERR "error"

#define IQ_AUTH    "jabber:iq:auth"
#define IQ_VERSION "jabber:iq:version"
#define IQ_ROSTER  "jabber:iq:roster"
#define IQ_PRIVATE "jabber:iq:private"
#define IQ_TIME "jabber:iq:time"
#define IQ_IDLE "jabber:iq:last"

#define JABBER_X_EVENT "jabber:x:event"

#define DISCO_INFO "http://jabber.org/protocol/disco#info"

#define MSGSTR_CHAT "chat"
#define MSGSTR_GCHAT "groupchat"
#define MSGSTR_NORMAL "normal"
// Not implemented in SieJC yet
//error
//headline

#define XMLNS_MUC "http://jabber.org/protocol/muc"
#define XMLNS_MUC_USER  "http://jabber.org/protocol/muc#user"
#define XMLNS_MUC_ADMIN "http://jabber.org/protocol/muc#admin"
#define XMLNS_BOOKMARKS "storage:bookmarks"
typedef enum {
	SUB_NONE,
	SUB_TO,
	SUB_FROM,
	SUB_BOTH
} JABBER_SUBSCRIPTION;

typedef enum {
	AFFILIATION_NONE,
	AFFILIATION_OUTCAST,
	AFFILIATION_MEMBER,
	AFFILIATION_ADMIN,
	AFFILIATION_OWNER
} JABBER_GC_AFFILIATION;

typedef enum {
	ROLE_NONE,
	ROLE_VISITOR,
	ROLE_PARTICIPANT,
	ROLE_MODERATOR
} JABBER_GC_ROLE;

////////////////////
#define PRESENCE_ONLINE 0
#define PRESENCE_CHAT 1
#define PRESENCE_AWAY 2
#define PRESENCE_XA 3
#define PRESENCE_DND 4
#define PRESENCE_INVISIBLE 5
#define PRESENCE_OFFLINE 6
#define PRESENCE_ERROR 7
#define PRESENCE_SUBSCRIBE 8
#define PRESENCE_SUBSCRIBED 9
#define PRESENCE_UNSUBSCRIBE 10
#define PRESENCE_UNSUBSCRIBED 11

// SASL errors
/*
The following SASL-related error conditions are defined: 

<aborted/> -- The receiving entity acknowledges an <abort/> element sent by the initiating entity; sent in reply to the <abort/> element. 
<incorrect-encoding/> -- The data provided by the initiating entity could not be processed because the [BASE64] encoding is incorrect (e.g., because the encoding does not adhere to the definition in Section 3 of [BASE64]); sent in reply to a <response/> element or an <auth/> element with initial response data. 
<invalid-authzid/> -- The authzid provided by the initiating entity is invalid, either because it is incorrectly formatted or because the initiating entity does not have permissions to authorize that ID; sent in reply to a <response/> element or an <auth/> element with initial response data. 
<invalid-mechanism/> -- The initiating entity did not provide a mechanism or requested a mechanism that is not supported by the receiving entity; sent in reply to an <auth/> element. 
<mechanism-too-weak/> -- The mechanism requested by the initiating entity is weaker than server policy permits for that initiating entity; sent in reply to a <response/> element or an <auth/> element with initial response data. 
<not-authorized/> -- The authentication failed because the initiating entity did not provide valid credentials (this includes but is not limited to the case of an unknown username); sent in reply to a <response/> element or an <auth/> element with initial response data. 
<temporary-auth-failure/> -- The authentication failed because of a temporary error condition within the receiving entity; sent in reply to an <auth/> element or <response/> element.
*/

#define SASLERR_ABORTED   "aborted"
#define SASLERR_BAD_ENC   "incorrect-encoding"
#define SASLERR_AUTHZID   "invalid-authzid"
#define SASLERR_MECH      "invalid-mechanism"
#define SASLERR_MECHWEAK  "mechanism-too-weak"
#define SASLERR_NOTAUTH   "not-authorized"
#define SASLERR_TEMPFAIL  "temporary-auth-failure"
#endif
