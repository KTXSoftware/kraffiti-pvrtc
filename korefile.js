let project = new Project('kraffiti-pvrtc', __dirname);

project.dynlib = true;

project.addExclude('.git/**');
project.addExclude('build/**');

project.addFile('Sources/**');
project.addFile('Library/Include/**');

project.addIncludeDir('Library/Include');
if (platform === Platform.Windows) {
	project.addLibFor('Win32', 'Library/Windows_x86_32/PVRTexLib');
	project.addLibFor('x64', 'Library/Windows_x86_64/PVRTexLib');
}

resolve(project);
