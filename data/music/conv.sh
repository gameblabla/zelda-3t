for i in *.wav ; do 
    ffmpeg -i "$i" -acodec libvorbis -qscale:a 0 "$(basename "${i/.wav}").ogg"
done
