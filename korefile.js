const solution = new Solution("kraffiti-pvrtc");
const project = new Project("kraffiti-pvrtc");

solution.dynlib = true;

project.addExclude('.git/**');
project.addExclude('build/**');

project.addFile('Sources/**');
project.addFile('Libraries/PVRTexTool/Include/**');

project.addDefine('LIB_PVRTC');
project.addIncludeDir('Libraries/PVRTexTool/Include');
if (platform === Platform.Windows) {
	project.addLibFor('Win32', 'Libraries/PVRTexTool/Windows_x86_32/Static/PVRTexLib');
	project.addLibFor('x64', 'Libraries/PVRTexTool/Windows_x86_64/Static/PVRTexLib');
}
else if (platform === Platform.OSX) {
	project.addLib('Libraries/PVRTexTool/OSX_x86/Static/PVRTexLib.a');
}
else if (platform === Platform.Linux) {
	project.addLib('Libraries/PVRTexTool/Linux_x86_32/Static/PVRTexLib');
}

solution.addProject(project);

return solution;
