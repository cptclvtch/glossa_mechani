echo !!!WARNING!!! In order to run this script correctly, you need to install coan.exe, sed.exe and add them to your PATH environment variable.

echo Prepping publication folder
rm glossa_mechani.zip
rm -r ./glossa_mechani
rm glossa_mechani_documented.zip
rm -r ./glossa_mechani_documented
echo Prep finished.

#-----------------------
echo Generating documented version
mkdir -p ./glossa_mechani_documented
cp -r ../internal glossa_mechani_documented
cp -r ../algebra glossa_mechani_documented
cp -r ../memory_management glossa_mechani_documented
cp -r ../program_flow glossa_mechani_documented
    echo ---Generating markdown file for instruction list.
    tcc -E -P ../internal/instructions.c -D GENERATE_DOCUMENTATION -o ../_documentation/language_standard/instructions.md
    sed -i "s/summary>/summary>\n/g" ../_documentation/language_standard/instructions.md
cp -r ../_documentation glossa_mechani_documented
cp -r ../_examples glossa_mechani_documented

cp ../glossa_mechani.c glossa_mechani_documented
cp ../README.md glossa_mechani_documented

tar acvf glossa_mechani_documented.zip ./glossa_mechani_documented
rm -r glossa_mechani_documented
echo Documented version finished.

#-----------------------
echo Generating essential-only version
mkdir -p ./glossa_mechani
cp -r glossa_mechani_documented/* glossa_mechani
rm -r glossa_mechani/internal/testing
rm -r glossa_mechani/_documentation
rm -r glossa_mechani/_examples
rm glossa_mechani/internal/interpreter_loop_readout.c
rm glossa_mechani/README.md

coan source --replace glossa_mechani/* -U CLT -U TESTING -U CORE_IMPLEMENTATION_ONLY -R -F c --gag summary --gag warning

tar acvf glossa_mechani.zip ./glossa_mechani
rm -rf glossa_mechani
echo Essential-only version finished.

echo Branch generation complete!