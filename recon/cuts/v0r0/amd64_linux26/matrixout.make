#-- start of make_header -----------------

#====================================
#  Application matrixout
#
#   Generated Sun Feb 12 23:31:18 2012  by phuidv
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_matrixout_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_matrixout_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_matrixout

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_matrixout = /tmp/CMT_$(cuts_tag)_matrixout.make$(cmt_lock_pid)
else
#cmt_local_tagfile_matrixout = $(cuts_tag)_matrixout.make
cmt_local_tagfile_matrixout = $(bin)$(cuts_tag)_matrixout.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_matrixout = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_matrixout = $(cuts_tag).make
cmt_local_tagfile_matrixout = $(bin)$(cuts_tag).make
endif

endif

-include $(cmt_local_tagfile_matrixout)

ifdef cmt_matrixout_has_target_tag

ifdef READONLY
cmt_final_setup_matrixout = /tmp/CMT_cuts_matrixoutsetup.make
cmt_local_matrixout_makefile = /tmp/CMT_matrixout$(cmt_lock_pid).make
else
cmt_final_setup_matrixout = $(bin)cuts_matrixoutsetup.make
cmt_local_matrixout_makefile = $(bin)matrixout.make
endif

else

ifdef READONLY
cmt_final_setup_matrixout = /tmp/CMT_cutssetup.make
cmt_local_matrixout_makefile = /tmp/CMT_matrixout$(cmt_lock_pid).make
else
cmt_final_setup_matrixout = $(bin)cutssetup.make
cmt_local_matrixout_makefile = $(bin)matrixout.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_cutssetup.make
else
cmt_final_setup = $(bin)cutssetup.make
endif

matrixout ::


ifdef READONLY
matrixout ::
	@echo tags=$(tags)
	@echo cmt_local_tagfile=$(cmt_local_tagfile)
endif


dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'matrixout'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = matrixout/
matrixout::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

matrixout :: dirs  $(bin)matrixout${application_suffix}
	$(echo) "matrixout ok"

#-- end of application_header
#-- start of application

$(bin)matrixout${application_suffix} :: $(bin)matrixout.o $(use_stamps) $(matrixoutstamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)matrixout.o $(cmt_installarea_linkopts) $(matrixout_use_linkopts) $(matrixoutlinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
matrixoutinstallname = matrixout${application_suffix}

matrixout :: matrixoutinstall

install :: matrixoutinstall

matrixoutinstall :: $(install_dir)/$(matrixoutinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(matrixoutinstallname) :: $(bin)$(matrixoutinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(matrixoutinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##matrixoutclean :: matrixoutuninstall

uninstall :: matrixoutuninstall

matrixoutuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(matrixoutinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (matrixout.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),matrixoutclean)

#$(bin)matrixout_dependencies.make :: dirs

ifndef QUICK
$(bin)matrixout_dependencies.make : ../app/matrixout.C $(use_requirements) $(cmt_final_setup_matrixout)
	$(echo) "(matrixout.make) Rebuilding $@"; \
	  $(build_dependencies) matrixout -all_sources -out=$@ ../app/matrixout.C
endif

#$(matrixout_dependencies)

-include $(bin)matrixout_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)matrixout_dependencies.make : $(matrixout_C_dependencies)

$(bin)$(binobj)matrixout.o : $(matrixout_C_dependencies)
	$(cpp_echo) ../app/matrixout.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(matrixout_pp_cppflags) $(app_matrixout_pp_cppflags) $(matrixout_pp_cppflags) $(use_cppflags) $(matrixout_cppflags) $(app_matrixout_cppflags) $(matrixout_cppflags) $(matrixout_C_cppflags) -I../app ../app/matrixout.C

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: matrixoutclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(matrixout.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(matrixout.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_matrixout)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(matrixout.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(matrixout.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(matrixout.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

matrixoutclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) matrixout${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f matrixout${application_suffix}

#	@echo "------> (matrixout.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)matrixout.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf matrixout_deps matrixout_dependencies.make
#-- end of cleanup_objects ------
