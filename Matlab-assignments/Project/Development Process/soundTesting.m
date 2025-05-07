clear
clc
%% Test differnet type of sounds

% Audio read source: https://au.mathworks.com/help/matlab/ref/audioread.html
% Audi player source: https://au.mathworks.com/help/matlab/ref/audioplayer.html\

%{
% Useful features 

player = audioplayer(y, Fs); % Create an audio player object
play(player); % Play sound
pause(player); % Pause playback
resume(player); % Resume playback
stop(player); % Stop playback

%}
userInp = input("Which sound would you like to hear?:");

% Load in audio
% [waveform, frequency] = audioread()


% Movement audio
[pop1WV, pop1FS] = audioread('move1.wav');
[pop2WV, pop2FS] = audioread('move2.wav');
[pop3WV, pop3FS] = audioread('move3.wav');

% BGM audio
[bgm1WV, bgm1FS] = audioread('bgm1.wav');

% Other type of audio
[succWV, succFS] = audioread('success.wav'); % Success

% Store soundwave and frequency in arrays and cells to play random later
soundList = {pop1WV, pop2WV, pop3WV};
fsList = [pop1FS, pop2FS, pop3FS];

switch userInp
    case 1
        % Ha le lu ya
        load handel.mat
        nBits = 16;
        sound(y,Fs,nBits)
    case 2
        % Random Custom pop sound
        chosenSound = randi([1,3]);
        sound(soundList{chosenSound}, fsList(chosenSound)); 
        %fprintf('Type chosen sound %d\n', soundList{chosenSound});

    case 3
        % BGM custom
        f = audioplayer(bgm1WV, bgm1FS);
        play(f);
        userInp = input('Enter anything to stop BGM: ');
        stop(f);

    otherwise
        fprintf('Sorry, the sound %d is not available\n', userInp);
end

