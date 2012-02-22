#-- start of make_header -----------------

#====================================
#  Application energycorrect
#
#   Generated Wed Feb 22 13:22:02 2012  by phuidn
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_energycorrect_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_energycorrect_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_energycorrect

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_energycorrect = /tmp/CMT_$(cuts_tag)_energycorrect.make$(cmt_lock_pid)
else
#cmt_local_tagfile_energycorrect = $(cuts_tag)_energycorrect.make
cmt_local_tagfile_energycorrect = $(bin)$(cuts_tag)_energycorrect.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_energycorrect = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_energycorrect = $(cuts_tag).make
cmt_local_tagfile_energycorrect = $(bin)$(cuts_tag).make
endif

endif

-include $(cmt_local_tagfile_energycorrect)

ifdef cmt_energycorrect_has_target_tag

ifdef READONLY
cmt_final_setup_energycorrect = /tmp/CMT_cuts_energycorrectsetup.make
cmt_local_energycorrect_makefile = /tmp/CMT_energycorrect$(cmt_lock_pid).make
else
cmt_final_setup_energycorrect = $(bin)cuts_energycorrectsetup.make
cmt_local_energycorrect_makefile = $(bin)energycorrect.make
endif

else

ifdef READONLY
cmt_final_setup_energycorrect = /tmp/CMT_cutssetup.make
cmt_local_energycorrect_makefile = /tmp/CMT_energycorrect$(cmt_lock_pid).make
else
cmt_final_setup_energycorrect = $(bin)cutssetup.make
cmt_local_energycorrect_makefile = $(bin)energycorrect.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_cutssetup.make
else
cmt_final_setup = $(bin)cutssetup.make
endif

energycorrect ::


ifdef READONLY
energycorrect ::
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
	$(echo) 'energycorrect'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = energycorrect/
energycorrect::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

energycorrect :: dirs  $(bin)energycorrect${application_suffix}
	$(echo) "energycorrect ok"

#-- end of application_header
#-- start of application

$(bin)energycorrect${application_suffix} :: $(bin)energycorrectnopython.o $(use_stamps) $(energycorrectstamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)energycorrectnopython.o $(cmt_installarea_linkopts) $(energycorrect_use_linkopts) $(energycorrectlinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
energycorrectinstallname = energycorrect${application_suffix}

energycorrect :: energycorrectinstall

install :: energycorrectinstall

energycorrectinstall :: $(install_dir)/$(energycorrectinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(energycorrectinstallname) :: $(bin)$(energycorrectinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(energycorrectinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##energycorrectclean :: energycorrectuninstall

uninstall :: energycorrectuninstall

energycorrectuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(energycorrectinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (energycorrect.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),energycorrectclean)

#$(bin)energycorrect_dependencies.make :: dirs

ifndef QUICK
$(bin)energycorrect_dependencies.make : ../app/energycorrectnopython.C $(use_requirements) $(cmt_final_setup_energycorrect)
	$(echo) "(energycorrect.make) Rebuilding $@"; \
	  $(build_dependencies) energycorrect -all_sources -out=$@ ../app/energycorrectnopython.C
endif

#$(energycorrect_dependencies)

-include $(bin)energycorrect_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)energycorrect_dependencies.make : $(energycorrectnopython_C_dependencies)

$(bin)$(binobj)energycorrectnopython.o : $(energycorrectnopython_C_dependencies)
	$(cpp_echo) ../app/energycorrectnopython.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(energycorrect_pp_cppflags) $(app_energycorrect_pp_cppflags) $(energycorrectnopython_pp_cppflags) $(use_cppflags) $(energycorrect_cppflags) $(app_energycorrect_cppflags) $(energycorrectnopython_cppflags) $(energycorrectnopython_C_cppflags) -I../app ../app/energycorrectnopython.C

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: energycorrectclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(energycorrect.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(energycorrect.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_energycorrect)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(energycorrect.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(energycorrect.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(energycorrect.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

energycorrectclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) energycorrect${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f energycorrect${application_suffix}

#	@echo "------> (energycorrect.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)energycorrectnopython.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf energycorrect_deps energycorrect_dependencies.make
#-- end of cleanup_objects ------
