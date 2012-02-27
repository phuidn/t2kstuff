#-- start of make_header -----------------

#====================================
#  Application makematrix
#
#   Generated Sun Feb 26 22:26:28 2012  by phuidn
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_makematrix_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_makematrix_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_makematrix

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_makematrix = /tmp/CMT_$(cuts_tag)_makematrix.make$(cmt_lock_pid)
else
#cmt_local_tagfile_makematrix = $(cuts_tag)_makematrix.make
cmt_local_tagfile_makematrix = $(bin)$(cuts_tag)_makematrix.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_makematrix = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_makematrix = $(cuts_tag).make
cmt_local_tagfile_makematrix = $(bin)$(cuts_tag).make
endif

endif

-include $(cmt_local_tagfile_makematrix)

ifdef cmt_makematrix_has_target_tag

ifdef READONLY
cmt_final_setup_makematrix = /tmp/CMT_cuts_makematrixsetup.make
cmt_local_makematrix_makefile = /tmp/CMT_makematrix$(cmt_lock_pid).make
else
cmt_final_setup_makematrix = $(bin)cuts_makematrixsetup.make
cmt_local_makematrix_makefile = $(bin)makematrix.make
endif

else

ifdef READONLY
cmt_final_setup_makematrix = /tmp/CMT_cutssetup.make
cmt_local_makematrix_makefile = /tmp/CMT_makematrix$(cmt_lock_pid).make
else
cmt_final_setup_makematrix = $(bin)cutssetup.make
cmt_local_makematrix_makefile = $(bin)makematrix.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_cutssetup.make
else
cmt_final_setup = $(bin)cutssetup.make
endif

makematrix ::


ifdef READONLY
makematrix ::
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
	$(echo) 'makematrix'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = makematrix/
makematrix::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

makematrix :: dirs  $(bin)makematrix${application_suffix}
	$(echo) "makematrix ok"

#-- end of application_header
#-- start of application

$(bin)makematrix${application_suffix} :: $(bin)matrixout.o $(use_stamps) $(makematrixstamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)matrixout.o $(cmt_installarea_linkopts) $(makematrix_use_linkopts) $(makematrixlinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
makematrixinstallname = makematrix${application_suffix}

makematrix :: makematrixinstall

install :: makematrixinstall

makematrixinstall :: $(install_dir)/$(makematrixinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(makematrixinstallname) :: $(bin)$(makematrixinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(makematrixinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##makematrixclean :: makematrixuninstall

uninstall :: makematrixuninstall

makematrixuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(makematrixinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (makematrix.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),makematrixclean)

#$(bin)makematrix_dependencies.make :: dirs

ifndef QUICK
$(bin)makematrix_dependencies.make : ../app/matrixout.C $(use_requirements) $(cmt_final_setup_makematrix)
	$(echo) "(makematrix.make) Rebuilding $@"; \
	  $(build_dependencies) makematrix -all_sources -out=$@ ../app/matrixout.C
endif

#$(makematrix_dependencies)

-include $(bin)makematrix_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)makematrix_dependencies.make : $(matrixout_C_dependencies)

$(bin)$(binobj)matrixout.o : $(matrixout_C_dependencies)
	$(cpp_echo) ../app/matrixout.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(makematrix_pp_cppflags) $(app_makematrix_pp_cppflags) $(matrixout_pp_cppflags) $(use_cppflags) $(makematrix_cppflags) $(app_makematrix_cppflags) $(matrixout_cppflags) $(matrixout_C_cppflags) -I../app ../app/matrixout.C

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: makematrixclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(makematrix.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(makematrix.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_makematrix)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(makematrix.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(makematrix.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(makematrix.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

makematrixclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) makematrix${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f makematrix${application_suffix}

#	@echo "------> (makematrix.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)matrixout.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf makematrix_deps makematrix_dependencies.make
#-- end of cleanup_objects ------
