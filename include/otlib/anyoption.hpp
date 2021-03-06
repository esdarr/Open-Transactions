#ifndef _ANYOPTION_H
#define _ANYOPTION_H

#include "OTCommon.hpp"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>



#define COMMON_OPT 	1
#define COMMAND_OPT 	2
#define FILE_OPT 	3
#define COMMON_FLAG 	4
#define COMMAND_FLAG 	5
#define FILE_FLAG 	6

#define COMMAND_OPTION_TYPE  	1
#define COMMAND_FLAG_TYPE 	2
#define FILE_OPTION_TYPE  	3
#define FILE_FLAG_TYPE 		4 
#define UNKNOWN_TYPE 		5

#define DEFAULT_MAXOPTS 	10
#define MAX_LONG_PREFIX_LENGTH 	2

#define DEFAULT_MAXUSAGE	3
#define DEFAULT_MAXHELP         10	

#define TRUE_FLAG "true" 


class AnyOption 
{

public: /* the public interface */
EXPORT	AnyOption();
	AnyOption(int32_t maxoptions ); 
	AnyOption(int32_t maxoptions , int32_t maxcharoptions); 
EXPORT	~AnyOption();

	/* 
         * following set methods specifies the  
	 * special characters and delimiters 
	 * if not set traditional defaults will be used
         */

	void setCommandPrefixChar( char _prefix );   /* '-' in "-w" */
	void setCommandLongPrefix( char *_prefix );  /* '--' in "--width" */
	void setFileCommentChar( char _comment );    /* '#' in shellscripts */
	void setFileDelimiterChar( char _delimiter );/* ':' in "width : 100" */

	/* 
	 * provide the input for the options
         * like argv[] for commndline and the 
         * option file name  to use;
	 */

	void useCommandArgs( int32_t _argc, char **_argv );
	void useFiileName( const char *_filename );

	/* 
         * turn off the POSIX style options 
         * this means anything starting with a '-' or "--"
         * will be considered a valid option 
         * which alo means you cannot add a bunch of 
         * POIX options chars together like "-lr"  for "-l -r"
         * 
         */

	void noPOSIX();

	/*
         * prints warning verbose if you set anything wrong 
         */
	void setVerbose();


	/* 
         * there are two types of options  
         *
         * Option - has an associated value ( -w 100 )
         * Flag  - no value, just a boolean flag  ( -nogui )
         * 
	 * the options can be either a string ( GNU style )
         * or a character ( traditional POSIX style ) 
         * or both ( --width, -w )
         *
         * the options can be common to the commandline and 
         * the optionfile, or can belong only to either of 
         * commandline and optionfile
         *
         * following set methods, handle all the aboove 
	 * cases of options.
         */

	/* options comman to command line and option file */
	void setOption( const char *opt_string );
	void setOption( char  opt_char );
	void setOption( const char *opt_string , char opt_char );
	void setFlag( const char *opt_string );
	void setFlag( char  opt_char );
	void setFlag( const char *opt_string , char opt_char );

	/* options read from commandline only */
EXPORT	void setCommandOption( const char *opt_string );
EXPORT	void setCommandOption( char  opt_char );
EXPORT	void setCommandOption( const char *opt_string , char opt_char );
EXPORT	void setCommandFlag( const char *opt_string );
EXPORT	void setCommandFlag( char  opt_char );
EXPORT	void setCommandFlag( const char *opt_string , char opt_char );

	/* options read from an option file only  */
EXPORT	void setFileOption( const char *opt_string );
	void setFileOption( char  opt_char );
	void setFileOption( const char *opt_string , char opt_char );
	void setFileFlag( const char *opt_string );
	void setFileFlag( char  opt_char );
	void setFileFlag( const char *opt_string , char opt_char );

	/*
         * process the options, registerd using 
         * useCommandArgs() and useFileName();
         */
	void processOptions();  
	void processCommandArgs();
EXPORT	void processCommandArgs( int32_t max_args );
EXPORT	bool processFile();

	/*
         * process the specified options 
         */
EXPORT	void processCommandArgs( int32_t _argc, char **_argv );
	void processCommandArgs( int32_t _argc, char **_argv, int32_t max_args );
EXPORT	bool processFile( const char *_filename );
	
	/*
         * get the value of the options 
	 * will return NULL if no value is set 
         */
EXPORT	char *getValue( const char *_option );
EXPORT	bool  getFlag( const char *_option );
EXPORT	char *getValue( char _optchar );
EXPORT	bool  getFlag( char _optchar );

	/*
	 * Print Usage
	 */
EXPORT	void printUsage();
	void printAutoUsage();
EXPORT	void addUsage( const char *line );
	void printHelp();
        /* print auto usage printing for unknown options or flag */
	void autoUsagePrint(bool flag);
	
	/* 
         * get the argument count and arguments sans the options
         */
EXPORT	int32_t   getArgc();
EXPORT	char* getArgv( int32_t index );
EXPORT	bool  hasOptions();

private: /* the hidden data structure */
	int32_t argc;		/* commandline arg count  */
	char **argv;  		/* commndline args */
	const char* filename; 	/* the option file */
	char* appname; 	/* the application name from argv[0] */

	int32_t *new_argv; 		/* arguments sans options (index to argv) */
	int32_t new_argc;   	/* argument count sans the options */
	int32_t max_legal_args; 	/* ignore extra arguments */


	/* option strings storage + indexing */
	int32_t max_options; 	/* maximum number of options */
	const char **options; 	/* storage */
	int32_t *optiontype; 	/* type - common, command, file */
	int32_t *optionindex;	/* index into value storage */
	int32_t option_counter; 	/* counter for added options  */

	/* option chars storage + indexing */
	int32_t max_char_options; 	/* maximum number options */
	char *optionchars; 	/*  storage */
	int32_t *optchartype; 	/* type - common, command, file */
	int32_t *optcharindex; 	/* index into value storage */
	int32_t optchar_counter; 	/* counter for added options  */

	/* values */
	char **values; 		/* common value storage */
	int32_t g_value_counter; 	/* globally updated value index LAME! */

	/* help and usage */
	const char **usage; 	/* usage */
	int32_t max_usage_lines;	/* max usage lines reseverd */
	int32_t usage_lines;	/* number of usage lines */

	bool command_set;	/* if argc/argv were provided */
	bool file_set;		/* if a filename was provided */
	bool mem_allocated;     /* if memory allocated in init() */
	bool posix_style; 	/* enables to turn off POSIX style options */
	bool verbose;		/* silent|verbose */
	bool print_usage;	/* usage verbose */
	bool print_help;	/* help verbose */
	
	char opt_prefix_char;		/*  '-' in "-w" */
	char long_opt_prefix[MAX_LONG_PREFIX_LENGTH + 1]; /* '--' in "--width" */
	char file_delimiter_char;	/* ':' in width : 100 */
	char file_comment_char;		/*  '#' in "#this is a comment" */
	char equalsign;
	char comment;
	char delimiter;
	char endofline;
	char whitespace;
	char nullterminate;

	bool set;   //was static member
	bool once;  //was static member
	
	bool hasoptions;
	bool autousage;

private: /* the hidden utils */
	void init();	
	void init(int32_t maxopt, int32_t maxcharopt );	
	bool alloc();
	void cleanup();
	bool valueStoreOK();

	/* grow storage arrays as required */
	bool doubleOptStorage();
	bool doubleCharStorage();
	bool doubleUsageStorage();

	bool setValue( const char *option , char *value );
	bool setFlagOn( const char *option );
	bool setValue( char optchar , char *value);
	bool setFlagOn( char optchar );

	void addOption( const char* option , int32_t type );
	void addOption( char optchar , int32_t type );
	void addOptionError( const char *opt);
	void addOptionError( char opt);
	bool findFlag( char* value );
	void addUsageError( const char *line );
	bool CommandSet();
	bool FileSet();
	bool POSIX();

	char parsePOSIX( char* arg );
	int32_t parseGNU( char *arg );
	bool matchChar( char c );
	int32_t matchOpt( char *opt );

	/* dot file methods */
	char *readFile();
	char *readFile( const char* fname );
	bool consumeFile( char *buffer );
	void processLine( char *theline, int32_t length );
	char *chomp( char *str );
	void valuePairs( char *type, char *value ); 
	void justValue( char *value );

	void printVerbose( const char *msg );
	void printVerbose( char *msg );
	void printVerbose( char ch );
	void printVerbose( );


};

#endif /* ! _ANYOPTION_H */
