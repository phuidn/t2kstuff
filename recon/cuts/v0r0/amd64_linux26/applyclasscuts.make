#-- start of make_header -----------------

#====================================
#  Application applyclasscuts
#
#   Generated Fri Jan 27 12:46:36 2012  by phuidn
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_applyclasscuts_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_applyclasscuts_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_applyclasscuts

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_applyclasscuts = /tmp/CMT_$(cuts_tag)_applyclasscuts.make$(cmt_lock_pid)
else
#cmt_local_tagfile_applyclasscuts = $(cuts_tag)_applyclasscuts.make
cmt_local_tagfile_applyclasscuts = $(bin)$(cuts_tag)_applyclasscuts.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_applyclasscuts = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_applyclasscuts = $(cuts_tag).make
cmt_local_tagfile_applyclasscuts = $(bin)$(cuts_tag).make
endif

endif

-include $(cmt_local_tagfile_applyclasscuts)

ifdef cmt_applyclasscuts_has_target_tag

ifdef READONLY
cmt_final_setup_applyclasscuts = /tmp/CMT_cuts_applyclasscutssetup.make
cmt_local_applyclasscuts_makefile = /tmp/CMT_applyclasscuts$(cmt_lock_pid).make
else
cmt_final_setup_applyclasscuts = $(bin)cuts_applyclasscutssetup.make
cmt_local_applyclasscuts_makefile = $(bin)applyclasscuts.make
endif

else

ifdef READONLY
cmt_final_setup_applyclasscuts = /tmp/CMT_cutssetup.make
cmt_local_applyclasscuts_makefile = /tmp/CMT_applyclasscuts$(cmt_lock_pid).make
else
cmt_final_setup_applyclasscuts = $(bin)cutssetup.make
cmt_local_applyclasscuts_makefile = $(bin)applyclasscuts.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_cutssetup.make
else
cmt_final_setup = $(bin)cutssetup.make
endif

applyclasscuts ::


ifdef READONLY
applyclasscuts ::
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
	$(echo) 'applyclasscuts'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = applyclasscuts/
applyclasscuts::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

applyclasscuts :: dirs  $(bin)applyclasscuts${application_suffix}
	$(echo) "applyclasscuts ok"

#-- end of application_header
#-- start of application

$(bin)applyclasscuts${application_suffix} :: $(bin)applyclasscuts.o $(bin)classcuts.o $(use_stamps) $(applyclasscutsstamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)applyclasscuts.o $(bin)classcuts.o $(cmt_installarea_linkopts) $(applyclasscuts_use_linkopts) $(applyclasscutslinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
applyclasscutsinstallname = applyclasscuts${application_suffix}

applyclasscuts :: applyclasscutsinstall

install :: applyclasscutsinstall

applyclasscutsinstall :: $(install_dir)/$(applyclasscutsinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(applyclasscutsinstallname) :: $(bin)$(applyclasscutsinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(applyclasscutsinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##applyclasscutsclean :: applyclasscutsuninstall

uninstall :: applyclasscutsuninstall

applyclasscutsuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(applyclasscutsinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (applyclasscuts.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),applyclasscutsclean)

#$(bin)applyclasscuts_dependencies.make :: dirs

ifndef QUICK
$(bin)applyclasscuts_dependencies.make : ../app/applyclasscuts.C ../app/classcuts.C $(use_requirements) $(cmt_final_setup_applyclasscuts)
	$(echo) "(applyclasscuts.make) Rebuilding $@"; \
	  $(build_dependencies) applyclasscuts -all_sources -out=$@ ../app/applyclasscuts.C ../app/classcuts.C
endif

#$(applyclasscuts_dependencies)

-include $(bin)applyclasscuts_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)applyclasscuts_dependencies.make : $(applyclasscuts_C_dependencies)

$(bin)$(binobj)applyclasscuts.o : $(applyclasscuts_C_dependencies)
	$(cpp_echo) ../app/applyclasscuts.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(applyclasscuts_pp_cppflags) $(app_applyclasscuts_pp_cppflags) $(applyclasscuts_pp_cppflags) $(use_cppflags) $(applyclasscuts_cppflags) $(app_applyclasscuts_cppflags) $(applyclasscuts_cppflags) $(applyclasscuts_C_cppflags) -I../app ../app/applyclasscuts.C

#-- end of cpp ------
#-- start of cpp ------

$(bin)applyclasscuts_dependencies.make : $(classcuts_C_dependencies)

$(bin)$(binobj)classcuts.o : $(classcuts_C_dependencies)
	$(cpp_echo) ../app/classcuts.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(applyclasscuts_pp_cppflags) $(app_applyclasscuts_pp_cppflags) $(classcuts_pp_cppflags) $(use_cppflags) $(applyclasscuts_cppflags) $(app_applyclasscuts_cppflags) $(classcuts_cppflags) $(classcuts_C_cppflags) -I../app ../app/classcuts.C

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: applyclasscutsclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(applyclasscuts.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(applyclasscuts.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_applyclasscuts)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(applyclasscuts.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(applyclasscuts.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(applyclasscuts.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

applyclasscutsclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) applyclasscuts${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f applyclasscuts${application_suffix}

#	@echo "------> (applyclasscuts.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)applyclasscuts.o $(bin)classcuts.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf applyclasscuts_deps applyclasscuts_dependencies.make
#-- end of cleanup_objects ------
