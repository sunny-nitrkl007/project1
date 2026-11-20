function mdlApp_modify_runtime_lib
%MDLAPP_MODIFY_RUNTIME_LIB - Change runtime lib to R13/R7B common lib
% -------------------------------------------------------------------------
% Usage:
%   mdlApp_modify_runtime_lib
%
% Inputs:
%
% Description:
%   Edits mdlApp.mk, changing runtime lib to one for both R13 and R2007B
% -------------------------------------------------------------------------

% Determine name of file
filename = fullfile(pwd,'mdlApp_cat_ff',['mdlApp','.mk']);

% If file exists
if exist(filename,'file') == 2
    % Read file in
    fid = fopen(filename,'r');
    if fid > 0
        dataI = fread(fid,inf,'uint8=>char')';
        fclose(fid);

        % Find and remove lines
        dataO = regexprep(dataI,'lib_simulink/include_R2007B \\','lib_simulink/include_R2007B_and_R13 \');
        dataO = regexprep(dataO,'lib/libsl_rtw_R2007B\.a','lib/libsl_rtw_R2007B_and_R13.a');

        % Write back out if different
        if ~strcmp(dataI,dataO)
            fid = fopen(filename,'w');
            if fid > 0
                fprintf(fid,'%s',dataO);
                fclose(fid);
            end
        end
    end
end