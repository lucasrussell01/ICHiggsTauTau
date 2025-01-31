if [ -z $2 ]
then
    echo "Must specify <script input> <script output>"
    exit
fi


INPUT=$1
OUTPUT=$2


echo "Generating job $OUTPUT"

echo "cd $PWD" &> $OUTPUT
echo "export X509_USER_PROXY=$HOME/cms.proxy" >> $OUTPUT
echo "source /vols/grid/cms/setup.sh" >> $OUTPUT
#echo "export SCRAM_ARCH=slc5_amd64_gcc462" >> $OUTPUT
echo "export SCRAM_ARCH=slc6_amd64_gcc481" >> $OUTPUT
echo "eval \`scramv1 runtime -sh\`" >> $OUTPUT
echo "source $PWD/scripts/setup_libs.sh" >> $OUTPUT
echo "ulimit -c 0" >> $OUTPUT
hostname >> $OUTPUT
if [ "$INPUT" == "" ]; then :
elif [[ "$INPUT" == ./* ]];
then
  echo "$INPUT" >> $OUTPUT
else
  echo "./$INPUT" >> $OUTPUT
fi
chmod +x $OUTPUT
