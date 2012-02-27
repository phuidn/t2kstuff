#-- start of make_header -----------------

#====================================
#  Application classapplycuts
#
#   Generated Sun Feb 26 22:26:24 2012  by phuidn
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_classapplycuts_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_classapplycuts_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_classapplycuts

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_classapplycuts = /tmp/CMT_$(cuts_tag)_classapplycuts.make$(cmt_lock_pid)
else
#cmt_local_tagfile_classapplycuts = $(cuts_tag)_classapplycuts.make
cmt_local_tagfile_classapplycuts = $(bin)$(cuts_tag)_classapplycuts.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_classapplycuts = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_classapplycuts = $(cuts_tag).make
cmt_local_tagfile_classapplycuts = $(bin)$(cuts_tag).make
endif

endif

-include $(cmt_local_tagfile_classapplycuts)

ifdef cmt_classapplycuts_has_target_tag

ifdef READONLY
cmt_final_setup_classapplycuts = /tmp/CMT_cuts_classapplycutssetup.make
cmt_local_classapplycuts_makefile = /tmp/CMT_classapplycuts$(cmt_lock_pid).make
else
cmt_final_setup_classapplycuts = $(bin)cuts_classapplycutssetup.make
cmt_local_classapplycuts_makefile = $(bin)classapplycuts.make
endif

else

ifdef READONLY
cmt_final_setup_classapplycuts = /tmp/CMT_cutssetup.make
cmt_local_classapplycuts_makefile = /tmp/CMT_classapplycuts$(cmt_lock_pid).make
else
cmt_final_setup_classapplycuts = $(bin)cutssetup.make
cmt_local_classapplycuts_makefile = $(bin)classapplycuts.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_cutssetup.make
else
cmt_final_setup = $(bin)cutssetup.make
endif

classapplycuts ::


ifdef READONLY
classapplycuts ::
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
	$(echo) 'classapplycuts'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = classapplycuts/
classapplycuts::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

classapplycuts :: dirs  $(bin)classapplycuts${application_suffix}
	$(echo) "classapplycuts ok"

#-- end of application_header
#-- start of application

$(bin)classapplycuts${application_suffix} :: $(bin)classapplycuts.o $(bin)classcuts.o $(use_stamps) $(classapplycutsstamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)classapplycuts.o $(bin)classcuts.o $(cmt_installarea_linkopts) $(classapplycuts_use_linkopts) $(classapplycutslinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
classapplycutsinstallname = classapplycuts${application_suffix}

classapplycuts :: classapplycutsinstall

install :: classapplycutsinstall

classapplycutsinstall :: $(install_dir)/$(classapplycutsinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(classapplycutsinstallname) :: $(bin)$(classapplycutsinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(classapplycutsinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##classapplycutsclean :: classapplycutsuninstall

uninstall :: classapplycutsuninstall

classapplycutsuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(classapplycutsinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (classapplycuts.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),classapplycutsclean)

#$(bin)classapplycuts_dependencies.make :: dirs

ifndef QUICK
$(bin)classapplycuts_dependencies.make : ../app/classapplycuts.C ../app/classcuts.C $(use_requirements) $(cmt_final_setup_classapplycuts)
	$(echo) "(classapplycuts.make) Rebuilding $@"; \
	  $(build_dependencies) classapplycuts -all_sources -out=$@ ../app/classapplycuts.C ../app/classcuts.C
endif

#$(classapplycuts_dependencies)

-include $(bin)classapplycuts_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)classapplycuts_dependencies.make : $(classapplycuts_C_dependencies)

$(bin)$(binobj)classapplycuts.o : $(classapplycuts_C_dependencies)
	$(cpp_echo) ../app/classapplycuts.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(classapplycuts_pp_cppflags) $(app_classapplycuts_pp_cppflags) $(classapplycuts_pp_cppflags) $(use_cppflags) $(classapplycuts_cppflags) $(app_classapplycuts_cppflags) $(classapplycuts_cppflags) $(classapplycuts_C_cppflags) -I../app ../app/classapplycuts.C

#-- end of cpp ------
#-- start of cpp ------

$(bin)classapplycuts_dependencies.make : $(classcuts_C_dependencies)

$(bin)$(binobj)classcuts.o : $(classcuts_C_dependencies)
	$(cpp_echo) ../app/classcuts.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(classapplycuts_pp_cppflags) $(app_classapplycuts_pp_cppflags) $(classcuts_pp_cppflags) $(use_cppflags) $(classapplycuts_cppflags) $(app_classapplycuts_cppflags) $(classcuts_cppflags) $(classcuts_C_cppflags) -I../app ../app/classcuts.C

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: classapplycutsclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(classapplycuts.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(classapplycuts.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_classapplycuts)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(classapplycuts.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(classapplycuts.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(classapplycuts.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

classapplycutsclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) classapplycuts${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f classapplycuts${application_suffix}

#	@echo "------> (classapplycuts.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)classapplycuts.o $(bin)classcuts.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf classapplycuts_deps classapplycuts_dependencies.make
#-- end of cleanup_objects ------
