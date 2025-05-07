clear
clc
%% Checkbox
% Source:https://au.mathworks.com/help/matlab/ref/matlab.ui.control.checkbox.html

fig = uifigure;



% Create the checkbox
cbx1 = uicheckbox(fig, 'Text', 'Unclickable Checkbox', 'Position', [20, 220, 300, 22], 'Enable', 'off');  % Disabled
cbx2 = uicheckbox(fig, 'Text', 'Average Checkbox', 'Position', [20, 120, 300, 22]);
cbx3 = uicheckbox(fig, 'Text', 'Uncheckable Checkbox', 'Position', [20, 20, 300, 22]); 


% Set the callback function for the checkbox | from source
cbx1.ValueChangedFcn = @(src, event) checkboxChanged(src);
cbx2.ValueChangedFcn = @(src, event) checkboxChanged(src);
cbx3.ValueChangedFcn = @(src, event) resetCheckBox(cbx3);


% Callback function
function resetCheckBox(checkBox)
    checkBox.Value = 0;
end

function checkboxChanged(src)
    if src.Value
        disp('Checkbox is ticked.');
    else
        disp('Checkbox is unticked.');
    end
end

