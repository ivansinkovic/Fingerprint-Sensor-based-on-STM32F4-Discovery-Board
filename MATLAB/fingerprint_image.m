%clear;
delete(instrfindall);
clear s;

s = serial('COM21');
set(s, 'BaudRate', 115200);
set(s, 'Parity', 'none');
set(s, 'DataBits', 8);
set(s, 'StopBit', 1);
set(s, 'InputBufferSize', 64512 );
fopen(s);

while( true )
    pause(1)
    bytes = s.BytesAvailable;
    % analiza
    if bytes > 0
        break
    end
end

podatak=fread(s,[224 288],'uint8');
matrica=transpose(podatak);
slika = mat2gray(matrica,[0 255]);
imshow(slika);

fclose(s);
delete(s);