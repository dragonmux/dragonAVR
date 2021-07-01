# SPDX-License-Identifier: BSD-3-Clause

project(
	'dragonAVR',
	'cpp',
	version: '0.0.1',
	meson_version: '>= 0.53'
)

#targetChip = get_option('chip')
#if targetChip == 'unknown'
#	error('You must set the target AVR to use')
#endif

dragonAVR_dep = declare_dependency(
	#compile_args: '-D@0@'.format(targetChip.to_upper()),
	include_directories: include_directories('include')
)
