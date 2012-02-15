#-- start of make_header -----------------

#====================================
#  Application classhistcuts
#
#   Generated Sun Feb 12 23:31:00 2012  by phuidv
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_classhistcuts_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_classhistcuts_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_classhistcuts

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_classhistcuts = /tmp/CMT_$(cuts_tag)_classhistcuts.make$(cmt_lock_pid)
else
#cmt_local_tagfile_classhistcuts = $(cuts_tag)_classhistcuts.make
cmt_local_tagfile_classhistcuts = $(bin)$(cuts_tag)_classhistcuts.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_classhistcuts = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_classhistcuts = $(cuts_tag).make
cmt_local_tagfile_classhistcuts = $(bin)$(cuts_tag).make
endif

endif

-include $(cmt_local_tagfile_classhistcuts)

ifdef cmt_classhistcuts_has_target_tag

ifdef READONLY
cmt_final_setup_classhistcuts = /tmp/CMT_cuts_classhistcutssetup.make
cmt_local_classhistcuts_makefile = /tmp/CMT_classhistcuts$(cmt_lock_pid).make
else
cmt_final_setup_classhistcuts = $(bin)cuts_classhistcutssetup.make
cmt_local_classhistcuts_makefile = $(bin)classhistcuts.make
endif

else

ifdef READONLY
cmt_final_setup_classhistcuts = /tmp/CMT_cutssetup.make
cmt_local_classhistcuts_makefile = /tmp/CMT_classhistcuts$(cmt_lock_pid).make
else
cmt_final_setup_classhistcuts = $(bin)cutssetup.make
cmt_local_classhistcuts_makefile = $(bin)classhistcuts.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_cutssetup.make
else
cmt_final_setup = $(bin)cutssetup.make
endif

classhistcuts ::


ifdef READONLY
classhistcuts ::
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
	$(echo) 'classhistcuts'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = classhistcuts/
classhistcuts::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

classhistcuts :: dirs  $(bin)classhistcuts${application_suffix}
	$(echo) "classhistcuts ok"

#-- end of application_header
#-- start of application

$(bin)classhistcuts${application_suffix} :: $(bin)classhistcuts.o $(bin)classcuts.o $(use_stamps) $(classhistcutsstamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)classhistcuts.o $(bin)classcuts.o $(cmt_installarea_linkopts) $(classhistcuts_use_linkopts) $(classhistcutslinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
classhistcutsinstallname = classhistcuts${application_suffix}

classhistcuts :: classhistcutsinstall

install :: classhistcutsinstall

classhistcutsinstall :: $(install_dir)/$(classhistcutsinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(classhistcutsinstallname) :: $(bin)$(classhistcutsinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(classhistcutsinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##classhistcutsclean :: classhistcutsuninstall

uninstall :: classhistcutsuninstall

classhistcutsuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(classhistcutsinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (classhistcuts.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),classhistcutsclean)

#$(bin)classhistcuts_dependencies.make :: dirs

ifndef QUICK
$(bin)classhistcuts_dependencies.make : ../app/classhistcuts.C ../app/classcuts.C $(use_requirements) $(cmt_final_setup_classhistcuts)
	$(echo) "(classhistcuts.make) Rebuilding $@"; \
	  $(build_dependencies) classhistcuts -all_sources -out=$@ ../app/classhistcuts.C ../app/classcuts.C
endif

#$(classhistcuts_dependencies)

-include $(bin)classhistcuts_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)classhistcuts_dependencies.make : $(classhistcuts_C_dependencies)

$(bin)$(binobj)classhistcuts.o : $(classhistcuts_C_dependencies)
	$(cpp_echo) ../app/classhistcuts.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(classhistcuts_pp_cppflags) $(app_classhistcuts_pp_cppflags) $(classhistcuts_pp_cppflags) $(use_cppflags) $(classhistcuts_cppflags) $(app_classhistcuts_cppflags) $(classhistcuts_cppflags) $(classhistcuts_C_cppflags) -I../app ../app/classhistcuts.C

#-- end of cpp ------
#-- start of cpp ------

$(bin)classhistcuts_dependencies.make : $(classcuts_C_dependencies)

$(bin)$(binobj)classcuts.o : $(classcuts_C_dependencies)
	$(cpp_echo) ../app/classcuts.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(classhistcuts_pp_cppflags) $(app_classhistcuts_pp_cppflags) $(classcuts_pp_cppflags) $(use_cppflags) $(classhistcuts_cppflags) $(app_classhistcuts_cppflags) $(classcuts_cppflags) $(classcuts_C_cppflags) -I../app ../app/classcuts.C

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: classhistcutsclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(classhistcuts.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(classhistcuts.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_classhistcuts)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(classhistcuts.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(classhistcuts.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(classhistcuts.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

classhistcutsclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) classhistcuts${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f classhistcuts${application_suffix}

#	@echo "------> (classhistcuts.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)classhistcuts.o $(bin)classcuts.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf classhistcuts_deps classhistcuts_dependencies.make
#-- end of cleanup_objects ------
