function build_mdlApp

% Config
nMdl = 'mdlApp';

% Rename the .mdl
df = [nMdl,'_diary.txt'];
delete(df);
diary(df);

% Open model
load_system(nMdl);

% Generate code
rtwbuild(nMdl);

% Modify makefile
mdlApp_modify_runtime_lib;

% Exit MATLAB
diary off
drawnow;
quit;