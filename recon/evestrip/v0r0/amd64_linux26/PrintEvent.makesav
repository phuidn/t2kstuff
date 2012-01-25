#-- start of make_header -----------------

#====================================
#  Application PrintEvent
#
#   Generated Wed Jan 25 12:37:01 2012  by phuidv
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_PrintEvent_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_PrintEvent_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_PrintEvent

evestrip_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_PrintEvent = /tmp/CMT_$(evestrip_tag)_PrintEvent.make$(cmt_lock_pid)
else
#cmt_local_tagfile_PrintEvent = $(evestrip_tag)_PrintEvent.make
cmt_local_tagfile_PrintEvent = $(bin)$(evestrip_tag)_PrintEvent.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

evestrip_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_PrintEvent = /tmp/CMT_$(evestrip_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_PrintEvent = $(evestrip_tag).make
cmt_local_tagfile_PrintEvent = $(bin)$(evestrip_tag).make
endif

endif

-include $(cmt_local_tagfile_PrintEvent)

ifdef cmt_PrintEvent_has_target_tag

ifdef READONLY
cmt_final_setup_PrintEvent = /tmp/CMT_evestrip_PrintEventsetup.make
cmt_local_PrintEvent_makefile = /tmp/CMT_PrintEvent$(cmt_lock_pid).make
else
cmt_final_setup_PrintEvent = $(bin)evestrip_PrintEventsetup.make
cmt_local_PrintEvent_makefile = $(bin)PrintEvent.make
endif

else

ifdef READONLY
cmt_final_setup_PrintEvent = /tmp/CMT_evestripsetup.make
cmt_local_PrintEvent_makefile = /tmp/CMT_PrintEvent$(cmt_lock_pid).make
else
cmt_final_setup_PrintEvent = $(bin)evestripsetup.make
cmt_local_PrintEvent_makefile = $(bin)PrintEvent.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_evestripsetup.make
else
cmt_final_setup = $(bin)evestripsetup.make
endif

PrintEvent ::


ifdef READONLY
PrintEvent ::
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
	$(echo) 'PrintEvent'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = PrintEvent/
PrintEvent::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

PrintEvent :: dirs  $(bin)PrintEvent${application_suffix}
	$(echo) "PrintEvent ok"

#-- end of application_header
#-- start of application

$(bin)PrintEvent${application_suffix} :: $(bin)PrintEvent.o $(use_stamps) $(PrintEventstamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)PrintEvent.o $(cmt_installarea_linkopts) $(PrintEvent_use_linkopts) $(PrintEventlinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
PrintEventinstallname = PrintEvent${application_suffix}

PrintEvent :: PrintEventinstall

install :: PrintEventinstall

PrintEventinstall :: $(install_dir)/$(PrintEventinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(PrintEventinstallname) :: $(bin)$(PrintEventinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(PrintEventinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##PrintEventclean :: PrintEventuninstall

uninstall :: PrintEventuninstall

PrintEventuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(PrintEventinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (PrintEvent.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),PrintEventclean)

#$(bin)PrintEvent_dependencies.make :: dirs

ifndef QUICK
$(bin)PrintEvent_dependencies.make : ../app/PrintEvent.cxx $(use_requirements) $(cmt_final_setup_PrintEvent)
	$(echo) "(PrintEvent.make) Rebuilding $@"; \
	  $(build_dependencies) PrintEvent -all_sources -out=$@ ../app/PrintEvent.cxx
endif

#$(PrintEvent_dependencies)

-include $(bin)PrintEvent_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)PrintEvent_dependencies.make : $(PrintEvent_cxx_dependencies)

$(bin)$(binobj)PrintEvent.o : $(PrintEvent_cxx_dependencies)
	$(cpp_echo) ../app/PrintEvent.cxx
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(PrintEvent_pp_cppflags) $(app_PrintEvent_pp_cppflags) $(PrintEvent_pp_cppflags) $(use_cppflags) $(PrintEvent_cppflags) $(app_PrintEvent_cppflags) $(PrintEvent_cppflags) $(PrintEvent_cxx_cppflags) -I../app ../app/PrintEvent.cxx

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: PrintEventclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(PrintEvent.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(PrintEvent.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_PrintEvent)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(PrintEvent.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(PrintEvent.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(PrintEvent.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

PrintEventclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) PrintEvent${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f PrintEvent${application_suffix}

#	@echo "------> (PrintEvent.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)PrintEvent.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf PrintEvent_deps PrintEvent_dependencies.make
#-- end of cleanup_objects ------
