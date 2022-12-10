:: set tools
SET GRAPHVIZ_DOT_EXE=%graphviz_dot%
SET DOXYGEN_EXE=%doxygen%
SET PLANTUML_JAR=%plantuml%
SET HHC_EXE=%hhc%

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
