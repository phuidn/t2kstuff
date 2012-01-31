#-- start of make_header -----------------

#====================================
#  Application magnetecal
#
#   Generated Mon Jan 30 23:57:05 2012  by phuidn
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_magnetecal_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_magnetecal_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_magnetecal

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_magnetecal = /tmp/CMT_$(cuts_tag)_magnetecal.make$(cmt_lock_pid)
else
#cmt_local_tagfile_magnetecal = $(cuts_tag)_magnetecal.make
cmt_local_tagfile_magnetecal = $(bin)$(cuts_tag)_magnetecal.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_magnetecal = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_magnetecal = $(cuts_tag).make
cmt_local_tagfile_magnetecal = $(bin)$(cuts_tag).make
endif

endif

-include $(cmt_local_tagfile_magnetecal)

ifdef cmt_magnetecal_has_target_tag

ifdef READONLY
cmt_final_setup_magnetecal = /tmp/CMT_cuts_magnetecalsetup.make
cmt_local_magnetecal_makefile = /tmp/CMT_magnetecal$(cmt_lock_pid).make
else
cmt_final_setup_magnetecal = $(bin)cuts_magnetecalsetup.make
cmt_local_magnetecal_makefile = $(bin)magnetecal.make
endif

else

ifdef READONLY
cmt_final_setup_magnetecal = /tmp/CMT_cutssetup.make
cmt_local_magnetecal_makefile = /tmp/CMT_magnetecal$(cmt_lock_pid).make
else
cmt_final_setup_magnetecal = $(bin)cutssetup.make
cmt_local_magnetecal_makefile = $(bin)magnetecal.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_cutssetup.make
else
cmt_final_setup = $(bin)cutssetup.make
endif

magnetecal ::


ifdef READONLY
magnetecal ::
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
	$(echo) 'magnetecal'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = magnetecal/
magnetecal::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

magnetecal :: dirs  $(bin)magnetecal${application_suffix}
	$(echo) "magnetecal ok"

#-- end of application_header
#-- start of application

$(bin)magnetecal${application_suffix} :: $(bin)maketree.o $(bin)cuts.o $(use_stamps) $(magnetecalstamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)maketree.o $(bin)cuts.o $(cmt_installarea_linkopts) $(magnetecal_use_linkopts) $(magnetecallinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
magnetecalinstallname = magnetecal${application_suffix}

magnetecal :: magnetecalinstall

install :: magnetecalinstall

magnetecalinstall :: $(install_dir)/$(magnetecalinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(magnetecalinstallname) :: $(bin)$(magnetecalinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(magnetecalinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##magnetecalclean :: magnetecaluninstall

uninstall :: magnetecaluninstall

magnetecaluninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(magnetecalinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (magnetecal.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),magnetecalclean)

#$(bin)magnetecal_dependencies.make :: dirs

ifndef QUICK
$(bin)magnetecal_dependencies.make : ../app/maketree.C ../app/cuts.C $(use_requirements) $(cmt_final_setup_magnetecal)
	$(echo) "(magnetecal.make) Rebuilding $@"; \
	  $(build_dependencies) magnetecal -all_sources -out=$@ ../app/maketree.C ../app/cuts.C
endif

#$(magnetecal_dependencies)

-include $(bin)magnetecal_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)magnetecal_dependencies.make : $(maketree_C_dependencies)

$(bin)$(binobj)maketree.o : $(maketree_C_dependencies)
	$(cpp_echo) ../app/maketree.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(magnetecal_pp_cppflags) $(app_magnetecal_pp_cppflags) $(maketree_pp_cppflags) $(use_cppflags) $(magnetecal_cppflags) $(app_magnetecal_cppflags) $(maketree_cppflags) $(maketree_C_cppflags) -I../app ../app/maketree.C

#-- end of cpp ------
#-- start of cpp ------

$(bin)magnetecal_dependencies.make : $(cuts_C_dependencies)

$(bin)$(binobj)cuts.o : $(cuts_C_dependencies)
	$(cpp_echo) ../app/cuts.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(magnetecal_pp_cppflags) $(app_magnetecal_pp_cppflags) $(cuts_pp_cppflags) $(use_cppflags) $(magnetecal_cppflags) $(app_magnetecal_cppflags) $(cuts_cppflags) $(cuts_C_cppflags) -I../app ../app/cuts.C

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: magnetecalclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(magnetecal.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(magnetecal.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_magnetecal)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(magnetecal.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(magnetecal.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(magnetecal.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

magnetecalclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) magnetecal${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f magnetecal${application_suffix}

#	@echo "------> (magnetecal.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)maketree.o $(bin)cuts.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf magnetecal_deps magnetecal_dependencies.make
#-- end of cleanup_objects ------
