function convert_and_build_mdlFxPt

% Config
oMdl = 'mdlFxPt';
nMdl = 'mdlFxPt_R7B';

% Convert the model
AutoConvertModel(oMdl,[oMdl,'.cdd']);

% Rename the .mdl
diary([nMdl,'_diary.txt']);
delete([nMdl,'.mdl']);
movefile([oMdl,'.mdl'],[nMdl,'.mdl']);

% Open model
load_system(nMdl);

% Change options
set_param(nMdl,'Cat_ModifyGeneratedCodeForR13CommonLib','on' );
set_param(nMdl,'CatCalToolConfig_CreateEMC2'           ,'off');

% Generate code
rtwbuild(nMdl);

% Exit MATLAB
diary off
quit;