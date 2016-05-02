const solution = new Solution("kraffiti-pvrtc");
const project = new Project("kraffiti-pvrtc");

solution.dynlib = true;

project.addExclude('.git/**');
project.addExclude('build/**');

project.addFile('Sources/**');
project.addFile('Library/Include/**');

project.addDefine('LIB_PVRTC');
project.addIncludeDir('Library/Include');
if (platform === Platform.Windows) {
	project.addLibFor('Win32', 'Library/Windows_x86_32/PVRTexLib');
	project.addLibFor('x64', 'Library/Windows_x86_64/PVRTexLib');
}

solution.addProject(project);

return solution;
