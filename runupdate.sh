for dir in `ls`
do 
  if [ -d $dir ]; then
    echo $dir
    cd $dir
    git pull
    cd ..
  fi
done
