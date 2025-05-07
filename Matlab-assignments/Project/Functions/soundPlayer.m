% Sound Credit
% BGM: https://www.chosic.com/download-audio/59619/
% Beating a level sfx: https://pixabay.com/sound-effects/search/level/

function [] = soundPlayer(soundType)
    persistent bgmAudio
    % Load in all relevant sounds
    % Movement audio
    [pop1WV, pop1FS] = audioread('Sound\move1.wav');
    [pop2WV, pop2FS] = audioread('Sound\move2.wav');
    [pop3WV, pop3FS] = audioread('Sound\move3.wav');
    
    % Store soundwave and frequency in arrays and cells to play random later
    moveSoundList = {pop1WV, pop2WV, pop3WV};
    moveFSList = [pop1FS, pop2FS, pop3FS];   
    
    % Load BGM audio
    [bgm1WV, bgm1FS] = audioread('Sound\bgm1.wav');
    [bgm2WV, bgm2FS] = audioread('Sound\bgm2.wav');
    
    % Store BGM Audio to randomize later
    bgmSoundList = {bgm1WV, bgm2WV};
    bgmFSList = [bgm1FS, bgm2FS];

    % Other type of audio
    [succWV, succFS] = audioread('Sound\success.wav'); % Success

    switch soundType
        case 'move'
            chosenSound = randi([1,length(moveSoundList)]);
            adjustedVolume = moveSoundList{chosenSound} * 0.2;
            sound(adjustedVolume, moveFSList(chosenSound)); 
        case 'bgmPlay' % Initialized only once
                chosenSound = randi([1, length(bgmSoundList)]);
                adjustedVolume = bgmSoundList{chosenSound} * 0.4;
            
                bgmAudio = audioplayer(adjustedVolume, bgmFSList(chosenSound));
                play(bgmAudio);
                
        case 'bgmToggle' % Toggled by shop menu
            if isplaying(bgmAudio)
                stop(bgmAudio)
            else
                chosenSound = randi([1, length(bgmSoundList)]);
                adjustedVolume = bgmSoundList{chosenSound} * 0.4;
            
                bgmAudio = audioplayer(adjustedVolume, bgmFSList(chosenSound));
                play(bgmAudio);
            end
            

        case 'success'
            adjustedVolume = succWV * 0.4;
            sound(adjustedVolume, succFS);

        otherwise 
            fprintf('No sound found: %s\n', soundType);
    end
end
