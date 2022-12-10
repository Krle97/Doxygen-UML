:: set tools
:: either use environment variables or hard-coded paths
SET GRAPHVIZ_DOT_EXE=%graphviz_dot%
IF not defined GRAPHVIZ_DOT_EXE GOTO :GRAPHVIZ_undef
SET DOXYGEN_EXE=%doxygen%
IF not defined DOXYGEN_EXE GOTO :DOXYGEN_undef
SET PLANTUML_JAR=%plantuml%
IF not defined PLANTUML_JAR GOTO :PLANTUML_undef
SET HHC_EXE=%hhc%
IF not defined HHC_EXE GOTO :HHC_undef

:: naming
SET PRJ_NAME=WatchDog Module
SET CHM_FILE_NAME=WDG

:: Set aliases (must be enclosed with "")
SET ALIAS_1="callsequence=@par Call sequence:^^"
SET ALIAS_2="globals=@par Globals:^^"

SET ALIASES_ALL=%ALIAS_1% %ALIAS_2%

:: get absolute project base file
PUSHD %CD%\..\..
SET PROJECT_BASE=%CD%
POPD

:: set pathnames used by doxygen
SET SOURCE_PATH="%PROJECT_BASE%/01_Source_Code/WDG"
SET EXLUDE_PATH=""

:: delete old image and CHM file(s)
DEL /F .\*.chm
DEL /F .\*.chw
DEL /F .\*.log

:: call doxygen 
%DOXYGEN_EXE% Doxyfile.doxy 2> Doxygen_Errors.log

:: delete html folder
RD /s/q %CD%\html
GOTO:eof

:GRAPHVIZ_undef
ECHO Either 'graphviz_dot' envirnoment variable is undefined or GRAPHVIZ_DOT_EXE is not SET. > ErrorLog.log
GOTO:eof

:DOXYGEN_undef
ECHO Either 'doxygen' envirnoment variable is undefined or DOXYGEN_EXE is not SET. > ErrorLog.log
GOTO:eof

:PLANTUML_undef
ECHO Either 'plantuml' envirnoment variable is undefined or PLANTUML_JAR is not SET. > ErrorLog.log
GOTO:eof

:HHC_undef
ECHO Either 'hhc' envirnoment variable is undefined or HHC_EXE is not SET. > ErrorLog.log
GOTO:eof