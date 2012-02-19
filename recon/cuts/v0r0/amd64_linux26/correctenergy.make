#-- start of make_header -----------------

#====================================
#  Application correctenergy
#
#   Generated Sun Feb 19 15:35:51 2012  by phuidn
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_correctenergy_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_correctenergy_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_correctenergy

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_correctenergy = /tmp/CMT_$(cuts_tag)_correctenergy.make$(cmt_lock_pid)
else
#cmt_local_tagfile_correctenergy = $(cuts_tag)_correctenergy.make
cmt_local_tagfile_correctenergy = $(bin)$(cuts_tag)_correctenergy.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_correctenergy = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_correctenergy = $(cuts_tag).make
cmt_local_tagfile_correctenergy = $(bin)$(cuts_tag).make
endif

endif

-include $(cmt_local_tagfile_correctenergy)

ifdef cmt_correctenergy_has_target_tag

ifdef READONLY
cmt_final_setup_correctenergy = /tmp/CMT_cuts_correctenergysetup.make
cmt_local_correctenergy_makefile = /tmp/CMT_correctenergy$(cmt_lock_pid).make
else
cmt_final_setup_correctenergy = $(bin)cuts_correctenergysetup.make
cmt_local_correctenergy_makefile = $(bin)correctenergy.make
endif

else

ifdef READONLY
cmt_final_setup_correctenergy = /tmp/CMT_cutssetup.make
cmt_local_correctenergy_makefile = /tmp/CMT_correctenergy$(cmt_lock_pid).make
else
cmt_final_setup_correctenergy = $(bin)cutssetup.make
cmt_local_correctenergy_makefile = $(bin)correctenergy.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_cutssetup.make
else
cmt_final_setup = $(bin)cutssetup.make
endif

correctenergy ::


ifdef READONLY
correctenergy ::
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
	$(echo) 'correctenergy'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = correctenergy/
correctenergy::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

correctenergy :: dirs  $(bin)correctenergy${application_suffix}
	$(echo) "correctenergy ok"

#-- end of application_header
#-- start of application

$(bin)correctenergy${application_suffix} :: $(bin)energycorrect.o $(use_stamps) $(correctenergystamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)energycorrect.o $(cmt_installarea_linkopts) $(correctenergy_use_linkopts) $(correctenergylinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
correctenergyinstallname = correctenergy${application_suffix}

correctenergy :: correctenergyinstall

install :: correctenergyinstall

correctenergyinstall :: $(install_dir)/$(correctenergyinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(correctenergyinstallname) :: $(bin)$(correctenergyinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(correctenergyinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##correctenergyclean :: correctenergyuninstall

uninstall :: correctenergyuninstall

correctenergyuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(correctenergyinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (correctenergy.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),correctenergyclean)

#$(bin)correctenergy_dependencies.make :: dirs

ifndef QUICK
$(bin)correctenergy_dependencies.make : ../app/energycorrect.C $(use_requirements) $(cmt_final_setup_correctenergy)
	$(echo) "(correctenergy.make) Rebuilding $@"; \
	  $(build_dependencies) correctenergy -all_sources -out=$@ ../app/energycorrect.C
endif

#$(correctenergy_dependencies)

-include $(bin)correctenergy_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)correctenergy_dependencies.make : $(energycorrect_C_dependencies)

$(bin)$(binobj)energycorrect.o : $(energycorrect_C_dependencies)
	$(cpp_echo) ../app/energycorrect.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(correctenergy_pp_cppflags) $(app_correctenergy_pp_cppflags) $(energycorrect_pp_cppflags) $(use_cppflags) $(correctenergy_cppflags) $(app_correctenergy_cppflags) $(energycorrect_cppflags) $(energycorrect_C_cppflags) -I../app ../app/energycorrect.C

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: correctenergyclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(correctenergy.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(correctenergy.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_correctenergy)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(correctenergy.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(correctenergy.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(correctenergy.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

correctenergyclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) correctenergy${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f correctenergy${application_suffix}

#	@echo "------> (correctenergy.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)energycorrect.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf correctenergy_deps correctenergy_dependencies.make
#-- end of cleanup_objects ------
