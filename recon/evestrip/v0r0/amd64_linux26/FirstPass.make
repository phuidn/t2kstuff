#-- start of make_header -----------------

#====================================
#  Application FirstPass
#
#   Generated Wed Jan 25 12:37:03 2012  by phuidv
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_FirstPass_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_FirstPass_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_FirstPass

evestrip_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_FirstPass = /tmp/CMT_$(evestrip_tag)_FirstPass.make$(cmt_lock_pid)
else
#cmt_local_tagfile_FirstPass = $(evestrip_tag)_FirstPass.make
cmt_local_tagfile_FirstPass = $(bin)$(evestrip_tag)_FirstPass.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

evestrip_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_FirstPass = /tmp/CMT_$(evestrip_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_FirstPass = $(evestrip_tag).make
cmt_local_tagfile_FirstPass = $(bin)$(evestrip_tag).make
endif

endif

-include $(cmt_local_tagfile_FirstPass)

ifdef cmt_FirstPass_has_target_tag

ifdef READONLY
cmt_final_setup_FirstPass = /tmp/CMT_evestrip_FirstPasssetup.make
cmt_local_FirstPass_makefile = /tmp/CMT_FirstPass$(cmt_lock_pid).make
else
cmt_final_setup_FirstPass = $(bin)evestrip_FirstPasssetup.make
cmt_local_FirstPass_makefile = $(bin)FirstPass.make
endif

else

ifdef READONLY
cmt_final_setup_FirstPass = /tmp/CMT_evestripsetup.make
cmt_local_FirstPass_makefile = /tmp/CMT_FirstPass$(cmt_lock_pid).make
else
cmt_final_setup_FirstPass = $(bin)evestripsetup.make
cmt_local_FirstPass_makefile = $(bin)FirstPass.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_evestripsetup.make
else
cmt_final_setup = $(bin)evestripsetup.make
endif

FirstPass ::


ifdef READONLY
FirstPass ::
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
	$(echo) 'FirstPass'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = FirstPass/
FirstPass::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

FirstPass :: dirs  $(bin)FirstPass${application_suffix}
	$(echo) "FirstPass ok"

#-- end of application_header
#-- start of application

$(bin)FirstPass${application_suffix} :: $(bin)analysis.o $(use_stamps) $(FirstPassstamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)analysis.o $(cmt_installarea_linkopts) $(FirstPass_use_linkopts) $(FirstPasslinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
FirstPassinstallname = FirstPass${application_suffix}

FirstPass :: FirstPassinstall

install :: FirstPassinstall

FirstPassinstall :: $(install_dir)/$(FirstPassinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(FirstPassinstallname) :: $(bin)$(FirstPassinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(FirstPassinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##FirstPassclean :: FirstPassuninstall

uninstall :: FirstPassuninstall

FirstPassuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(FirstPassinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (FirstPass.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),FirstPassclean)

#$(bin)FirstPass_dependencies.make :: dirs

ifndef QUICK
$(bin)FirstPass_dependencies.make : ../app/analysis.cxx $(use_requirements) $(cmt_final_setup_FirstPass)
	$(echo) "(FirstPass.make) Rebuilding $@"; \
	  $(build_dependencies) FirstPass -all_sources -out=$@ ../app/analysis.cxx
endif

#$(FirstPass_dependencies)

-include $(bin)FirstPass_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)FirstPass_dependencies.make : $(analysis_cxx_dependencies)

$(bin)$(binobj)analysis.o : $(analysis_cxx_dependencies)
	$(cpp_echo) ../app/analysis.cxx
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(FirstPass_pp_cppflags) $(app_FirstPass_pp_cppflags) $(analysis_pp_cppflags) $(use_cppflags) $(FirstPass_cppflags) $(app_FirstPass_cppflags) $(analysis_cppflags) $(analysis_cxx_cppflags) -I../app ../app/analysis.cxx

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: FirstPassclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(FirstPass.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(FirstPass.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_FirstPass)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(FirstPass.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(FirstPass.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(FirstPass.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

FirstPassclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) FirstPass${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f FirstPass${application_suffix}

#	@echo "------> (FirstPass.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)analysis.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf FirstPass_deps FirstPass_dependencies.make
#-- end of cleanup_objects ------
