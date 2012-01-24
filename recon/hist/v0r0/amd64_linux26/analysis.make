#-- start of make_header -----------------

#====================================
#  Application analysis
#
#   Generated Tue Jan 24 11:38:55 2012  by phuidv
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_analysis_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_analysis_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_analysis

hist_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_analysis = /tmp/CMT_$(hist_tag)_analysis.make$(cmt_lock_pid)
else
#cmt_local_tagfile_analysis = $(hist_tag)_analysis.make
cmt_local_tagfile_analysis = $(bin)$(hist_tag)_analysis.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

hist_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_analysis = /tmp/CMT_$(hist_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_analysis = $(hist_tag).make
cmt_local_tagfile_analysis = $(bin)$(hist_tag).make
endif

endif

-include $(cmt_local_tagfile_analysis)

ifdef cmt_analysis_has_target_tag

ifdef READONLY
cmt_final_setup_analysis = /tmp/CMT_hist_analysissetup.make
cmt_local_analysis_makefile = /tmp/CMT_analysis$(cmt_lock_pid).make
else
cmt_final_setup_analysis = $(bin)hist_analysissetup.make
cmt_local_analysis_makefile = $(bin)analysis.make
endif

else

ifdef READONLY
cmt_final_setup_analysis = /tmp/CMT_histsetup.make
cmt_local_analysis_makefile = /tmp/CMT_analysis$(cmt_lock_pid).make
else
cmt_final_setup_analysis = $(bin)histsetup.make
cmt_local_analysis_makefile = $(bin)analysis.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_histsetup.make
else
cmt_final_setup = $(bin)histsetup.make
endif

analysis ::


ifdef READONLY
analysis ::
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
	$(echo) 'analysis'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = analysis/
analysis::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

analysis :: dirs  $(bin)analysis${application_suffix}
	$(echo) "analysis ok"

#-- end of application_header
#-- start of application

$(bin)analysis${application_suffix} :: $(bin)analysis.o $(bin)cuts.o $(use_stamps) $(analysisstamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)analysis.o $(bin)cuts.o $(cmt_installarea_linkopts) $(analysis_use_linkopts) $(analysislinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
analysisinstallname = analysis${application_suffix}

analysis :: analysisinstall

install :: analysisinstall

analysisinstall :: $(install_dir)/$(analysisinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(analysisinstallname) :: $(bin)$(analysisinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(analysisinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##analysisclean :: analysisuninstall

uninstall :: analysisuninstall

analysisuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(analysisinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (analysis.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),analysisclean)

#$(bin)analysis_dependencies.make :: dirs

ifndef QUICK
$(bin)analysis_dependencies.make : ../app/analysis.C ../app/cuts.C $(use_requirements) $(cmt_final_setup_analysis)
	$(echo) "(analysis.make) Rebuilding $@"; \
	  $(build_dependencies) analysis -all_sources -out=$@ ../app/analysis.C ../app/cuts.C
endif

#$(analysis_dependencies)

-include $(bin)analysis_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)analysis_dependencies.make : $(analysis_C_dependencies)

$(bin)$(binobj)analysis.o : $(analysis_C_dependencies)
	$(cpp_echo) ../app/analysis.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(analysis_pp_cppflags) $(app_analysis_pp_cppflags) $(analysis_pp_cppflags) $(use_cppflags) $(analysis_cppflags) $(app_analysis_cppflags) $(analysis_cppflags) $(analysis_C_cppflags) -I../app ../app/analysis.C

#-- end of cpp ------
#-- start of cpp ------

$(bin)analysis_dependencies.make : $(cuts_C_dependencies)

$(bin)$(binobj)cuts.o : $(cuts_C_dependencies)
	$(cpp_echo) ../app/cuts.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(analysis_pp_cppflags) $(app_analysis_pp_cppflags) $(cuts_pp_cppflags) $(use_cppflags) $(analysis_cppflags) $(app_analysis_cppflags) $(cuts_cppflags) $(cuts_C_cppflags) -I../app ../app/cuts.C

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: analysisclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(analysis.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(analysis.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_analysis)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(analysis.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(analysis.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(analysis.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

analysisclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) analysis${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f analysis${application_suffix}

#	@echo "------> (analysis.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)analysis.o $(bin)cuts.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf analysis_deps analysis_dependencies.make
#-- end of cleanup_objects ------
