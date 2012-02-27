#-- start of make_header -----------------

#====================================
#  Application applycuts
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

cmt_applycuts_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_applycuts_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_applycuts

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_applycuts = /tmp/CMT_$(cuts_tag)_applycuts.make$(cmt_lock_pid)
else
#cmt_local_tagfile_applycuts = $(cuts_tag)_applycuts.make
cmt_local_tagfile_applycuts = $(bin)$(cuts_tag)_applycuts.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_applycuts = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_applycuts = $(cuts_tag).make
cmt_local_tagfile_applycuts = $(bin)$(cuts_tag).make
endif

endif

-include $(cmt_local_tagfile_applycuts)

ifdef cmt_applycuts_has_target_tag

ifdef READONLY
cmt_final_setup_applycuts = /tmp/CMT_cuts_applycutssetup.make
cmt_local_applycuts_makefile = /tmp/CMT_applycuts$(cmt_lock_pid).make
else
cmt_final_setup_applycuts = $(bin)cuts_applycutssetup.make
cmt_local_applycuts_makefile = $(bin)applycuts.make
endif

else

ifdef READONLY
cmt_final_setup_applycuts = /tmp/CMT_cutssetup.make
cmt_local_applycuts_makefile = /tmp/CMT_applycuts$(cmt_lock_pid).make
else
cmt_final_setup_applycuts = $(bin)cutssetup.make
cmt_local_applycuts_makefile = $(bin)applycuts.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_cutssetup.make
else
cmt_final_setup = $(bin)cutssetup.make
endif

applycuts ::


ifdef READONLY
applycuts ::
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
	$(echo) 'applycuts'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = applycuts/
applycuts::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

applycuts :: dirs  $(bin)applycuts${application_suffix}
	$(echo) "applycuts ok"

#-- end of application_header
#-- start of application

$(bin)applycuts${application_suffix} :: $(bin)applycuts.o $(bin)cuts.o $(use_stamps) $(applycutsstamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)applycuts.o $(bin)cuts.o $(cmt_installarea_linkopts) $(applycuts_use_linkopts) $(applycutslinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
applycutsinstallname = applycuts${application_suffix}

applycuts :: applycutsinstall

install :: applycutsinstall

applycutsinstall :: $(install_dir)/$(applycutsinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(applycutsinstallname) :: $(bin)$(applycutsinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(applycutsinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##applycutsclean :: applycutsuninstall

uninstall :: applycutsuninstall

applycutsuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(applycutsinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (applycuts.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),applycutsclean)

#$(bin)applycuts_dependencies.make :: dirs

ifndef QUICK
$(bin)applycuts_dependencies.make : ../app/applycuts.C ../app/cuts.C $(use_requirements) $(cmt_final_setup_applycuts)
	$(echo) "(applycuts.make) Rebuilding $@"; \
	  $(build_dependencies) applycuts -all_sources -out=$@ ../app/applycuts.C ../app/cuts.C
endif

#$(applycuts_dependencies)

-include $(bin)applycuts_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)applycuts_dependencies.make : $(applycuts_C_dependencies)

$(bin)$(binobj)applycuts.o : $(applycuts_C_dependencies)
	$(cpp_echo) ../app/applycuts.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(applycuts_pp_cppflags) $(app_applycuts_pp_cppflags) $(applycuts_pp_cppflags) $(use_cppflags) $(applycuts_cppflags) $(app_applycuts_cppflags) $(applycuts_cppflags) $(applycuts_C_cppflags) -I../app ../app/applycuts.C

#-- end of cpp ------
#-- start of cpp ------

$(bin)applycuts_dependencies.make : $(cuts_C_dependencies)

$(bin)$(binobj)cuts.o : $(cuts_C_dependencies)
	$(cpp_echo) ../app/cuts.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(applycuts_pp_cppflags) $(app_applycuts_pp_cppflags) $(cuts_pp_cppflags) $(use_cppflags) $(applycuts_cppflags) $(app_applycuts_cppflags) $(cuts_cppflags) $(cuts_C_cppflags) -I../app ../app/cuts.C

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: applycutsclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(applycuts.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(applycuts.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_applycuts)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(applycuts.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(applycuts.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(applycuts.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

applycutsclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) applycuts${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f applycuts${application_suffix}

#	@echo "------> (applycuts.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)applycuts.o $(bin)cuts.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf applycuts_deps applycuts_dependencies.make
#-- end of cleanup_objects ------
