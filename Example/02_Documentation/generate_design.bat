:: set tools
SET GRAPHVIZ_DOT_PATH=C:\Tools\Graphviz\bin
SET DOXYGEN_EXE=C:\Tools\doxygen\bin\doxygen.exe
SET PLANTUML_JAR=C:\Tools\plantuml\plantuml-1.2022.13.jar
SET HHC_EXE="C:/Program Files (x86)/HTML Help Workshop/hhc.exe"

:: get absolute project base file
SET PROJECT_BASE=%CD%\..
PUSHD %PROJECT_BASE%
SET PROJECT_BASE=%CD%
POPD

:: set pathnames used by doxygen
SET SOURCE_PATH="%PROJECT_BASE%/01_Source_Code/WDG"
SET EXLUDE_PATH=""

:: delete old image and CHM file(s)
DEL /F .\*.chm
DEL /F .\*.chw
DEL /F .\*.log

:: naming
SET CHM_FILE_NAME="WDG.chm"

:: call doxygen 
%DOXYGEN_EXE% Doxyfile.doxy 2> Doxygen_Errors.log

MOVE %CD%\html\*.chm
RD /s/q %CD%\html
