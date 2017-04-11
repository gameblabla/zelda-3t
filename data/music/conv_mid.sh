for i in *.mid ; do 
    timidity "$i" -Ow -o "$(basename "${i/.mid}").wav"
done
