#-- start of make_header -----------------

#====================================
#  Application hist
#
<<<<<<< HEAD:recon/cuts/v0r0/amd64_linux26/hist.make
#   Generated Thu Jan 26 16:59:21 2012  by phuidv
=======
#   Generated Fri Jan 27 17:18:11 2012  by phuidn
>>>>>>> 6e7e93cdbe2bbfcbda576add4ad10dbb2a6aa296:recon/cuts/v0r0/amd64_linux26/hist.make
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_hist_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_hist_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_hist

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_hist = /tmp/CMT_$(cuts_tag)_hist.make$(cmt_lock_pid)
else
#cmt_local_tagfile_hist = $(cuts_tag)_hist.make
cmt_local_tagfile_hist = $(bin)$(cuts_tag)_hist.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_hist = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_hist = $(cuts_tag).make
cmt_local_tagfile_hist = $(bin)$(cuts_tag).make
endif

endif

-include $(cmt_local_tagfile_hist)

ifdef cmt_hist_has_target_tag

ifdef READONLY
cmt_final_setup_hist = /tmp/CMT_cuts_histsetup.make
cmt_local_hist_makefile = /tmp/CMT_hist$(cmt_lock_pid).make
else
cmt_final_setup_hist = $(bin)cuts_histsetup.make
cmt_local_hist_makefile = $(bin)hist.make
endif

else

ifdef READONLY
cmt_final_setup_hist = /tmp/CMT_cutssetup.make
cmt_local_hist_makefile = /tmp/CMT_hist$(cmt_lock_pid).make
else
cmt_final_setup_hist = $(bin)cutssetup.make
cmt_local_hist_makefile = $(bin)hist.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_cutssetup.make
else
cmt_final_setup = $(bin)cutssetup.make
endif

hist ::


ifdef READONLY
hist ::
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
	$(echo) 'hist'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = hist/
hist::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

hist :: dirs  $(bin)hist${application_suffix}
	$(echo) "hist ok"

#-- end of application_header
#-- start of application

$(bin)hist${application_suffix} :: $(bin)hist.o $(bin)cuts.o $(use_stamps) $(histstamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)hist.o $(bin)cuts.o $(cmt_installarea_linkopts) $(hist_use_linkopts) $(histlinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
histinstallname = hist${application_suffix}

hist :: histinstall

install :: histinstall

histinstall :: $(install_dir)/$(histinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(histinstallname) :: $(bin)$(histinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(histinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##histclean :: histuninstall

uninstall :: histuninstall

histuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(histinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (hist.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),histclean)

#$(bin)hist_dependencies.make :: dirs

ifndef QUICK
$(bin)hist_dependencies.make : ../app/hist.C ../app/cuts.C $(use_requirements) $(cmt_final_setup_hist)
	$(echo) "(hist.make) Rebuilding $@"; \
	  $(build_dependencies) hist -all_sources -out=$@ ../app/hist.C ../app/cuts.C
endif

#$(hist_dependencies)

-include $(bin)hist_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)hist_dependencies.make : $(hist_C_dependencies)

$(bin)$(binobj)hist.o : $(hist_C_dependencies)
	$(cpp_echo) ../app/hist.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(hist_pp_cppflags) $(app_hist_pp_cppflags) $(hist_pp_cppflags) $(use_cppflags) $(hist_cppflags) $(app_hist_cppflags) $(hist_cppflags) $(hist_C_cppflags) -I../app ../app/hist.C

#-- end of cpp ------
#-- start of cpp ------

$(bin)hist_dependencies.make : $(cuts_C_dependencies)

$(bin)$(binobj)cuts.o : $(cuts_C_dependencies)
	$(cpp_echo) ../app/cuts.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(hist_pp_cppflags) $(app_hist_pp_cppflags) $(cuts_pp_cppflags) $(use_cppflags) $(hist_cppflags) $(app_hist_cppflags) $(cuts_cppflags) $(cuts_C_cppflags) -I../app ../app/cuts.C

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: histclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(hist.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(hist.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_hist)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(hist.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(hist.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(hist.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

histclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) hist${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f hist${application_suffix}

#	@echo "------> (hist.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)hist.o $(bin)cuts.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf hist_deps hist_dependencies.make
#-- end of cleanup_objects ------
