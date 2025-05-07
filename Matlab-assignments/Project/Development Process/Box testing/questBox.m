clear
clc
%% UI Testing

%% Quest box test
% Source: https://au.mathworks.com/help/matlab/ref/questdlg.html

% questdlg(quest,dlgtitle,btn1,btn2,defbtn)

function [] = runQuestdialogue()
    answer = questdlg('Would you like a dessert?', ...
	    'Dessert Menu', ...
	    'Ice cream','Cake','No thank you','No thank you');
    
    fprintf("%s\n", answer);
end

    