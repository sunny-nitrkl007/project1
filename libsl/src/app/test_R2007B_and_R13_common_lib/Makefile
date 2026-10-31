# Makefile
#   Make for the test app
#   Doesn't use OEL scripts right now

all: r7bAppFls

r13fixpt:
	# Change to directory and generate code
	cd mdlR13 && model_build.cmd mdlFxPt.buildescription

r13float:
	# Change to directory and generate code
	cd mdlR13 && model_build.cmd mdlFloat.buildescription

r7bfixpt:
	# Change to directory and generate code
	cd mdlR7b && build_FxPt.cmd

r7bfloat:
	# Change to directory and generate code
	cd mdlR7b && build_Float.cmd

r7bApp: r13fixpt r13float r7bfixpt r7bfloat
	# Change to directory and generate code
	cd mdlApp && build_mdlApp.cmd

r7bAppFls: r7bApp
	cd mdlApp\mdlApp_cat_ff && $(MAKE) -C gnu -f mdlApp.mk fls_dev

clean:
