#-- start of make_header -----------------

#====================================
#  Application magnetecalp0d
#
#   Generated Tue Jan 31 14:31:18 2012  by phuidn
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_magnetecalp0d_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_magnetecalp0d_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_magnetecalp0d

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_magnetecalp0d = /tmp/CMT_$(cuts_tag)_magnetecalp0d.make$(cmt_lock_pid)
else
#cmt_local_tagfile_magnetecalp0d = $(cuts_tag)_magnetecalp0d.make
cmt_local_tagfile_magnetecalp0d = $(bin)$(cuts_tag)_magnetecalp0d.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_magnetecalp0d = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_magnetecalp0d = $(cuts_tag).make
cmt_local_tagfile_magnetecalp0d = $(bin)$(cuts_tag).make
endif

endif

-include $(cmt_local_tagfile_magnetecalp0d)

ifdef cmt_magnetecalp0d_has_target_tag

ifdef READONLY
cmt_final_setup_magnetecalp0d = /tmp/CMT_cuts_magnetecalp0dsetup.make
cmt_local_magnetecalp0d_makefile = /tmp/CMT_magnetecalp0d$(cmt_lock_pid).make
else
cmt_final_setup_magnetecalp0d = $(bin)cuts_magnetecalp0dsetup.make
cmt_local_magnetecalp0d_makefile = $(bin)magnetecalp0d.make
endif

else

ifdef READONLY
cmt_final_setup_magnetecalp0d = /tmp/CMT_cutssetup.make
cmt_local_magnetecalp0d_makefile = /tmp/CMT_magnetecalp0d$(cmt_lock_pid).make
else
cmt_final_setup_magnetecalp0d = $(bin)cutssetup.make
cmt_local_magnetecalp0d_makefile = $(bin)magnetecalp0d.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_cutssetup.make
else
cmt_final_setup = $(bin)cutssetup.make
endif

magnetecalp0d ::


ifdef READONLY
magnetecalp0d ::
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
	$(echo) 'magnetecalp0d'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = magnetecalp0d/
magnetecalp0d::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

magnetecalp0d :: dirs  $(bin)magnetecalp0d${application_suffix}
	$(echo) "magnetecalp0d ok"

#-- end of application_header
#-- start of application

$(bin)magnetecalp0d${application_suffix} :: $(bin)maketree.o $(bin)cuts.o $(use_stamps) $(magnetecalp0dstamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)maketree.o $(bin)cuts.o $(cmt_installarea_linkopts) $(magnetecalp0d_use_linkopts) $(magnetecalp0dlinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
magnetecalp0dinstallname = magnetecalp0d${application_suffix}

magnetecalp0d :: magnetecalp0dinstall

install :: magnetecalp0dinstall

magnetecalp0dinstall :: $(install_dir)/$(magnetecalp0dinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(magnetecalp0dinstallname) :: $(bin)$(magnetecalp0dinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(magnetecalp0dinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##magnetecalp0dclean :: magnetecalp0duninstall

uninstall :: magnetecalp0duninstall

magnetecalp0duninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(magnetecalp0dinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (magnetecalp0d.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),magnetecalp0dclean)

#$(bin)magnetecalp0d_dependencies.make :: dirs

ifndef QUICK
$(bin)magnetecalp0d_dependencies.make : ../app/maketree.C ../app/cuts.C $(use_requirements) $(cmt_final_setup_magnetecalp0d)
	$(echo) "(magnetecalp0d.make) Rebuilding $@"; \
	  $(build_dependencies) magnetecalp0d -all_sources -out=$@ ../app/maketree.C ../app/cuts.C
endif

#$(magnetecalp0d_dependencies)

-include $(bin)magnetecalp0d_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)magnetecalp0d_dependencies.make : $(maketree_C_dependencies)

$(bin)$(binobj)maketree.o : $(maketree_C_dependencies)
	$(cpp_echo) ../app/maketree.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(magnetecalp0d_pp_cppflags) $(app_magnetecalp0d_pp_cppflags) $(maketree_pp_cppflags) $(use_cppflags) $(magnetecalp0d_cppflags) $(app_magnetecalp0d_cppflags) $(maketree_cppflags) $(maketree_C_cppflags) -I../app ../app/maketree.C

#-- end of cpp ------
#-- start of cpp ------

$(bin)magnetecalp0d_dependencies.make : $(cuts_C_dependencies)

$(bin)$(binobj)cuts.o : $(cuts_C_dependencies)
	$(cpp_echo) ../app/cuts.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(magnetecalp0d_pp_cppflags) $(app_magnetecalp0d_pp_cppflags) $(cuts_pp_cppflags) $(use_cppflags) $(magnetecalp0d_cppflags) $(app_magnetecalp0d_cppflags) $(cuts_cppflags) $(cuts_C_cppflags) -I../app ../app/cuts.C

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: magnetecalp0dclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(magnetecalp0d.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(magnetecalp0d.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_magnetecalp0d)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(magnetecalp0d.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(magnetecalp0d.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(magnetecalp0d.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

magnetecalp0dclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) magnetecalp0d${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f magnetecalp0d${application_suffix}

#	@echo "------> (magnetecalp0d.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)maketree.o $(bin)cuts.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf magnetecalp0d_deps magnetecalp0d_dependencies.make
#-- end of cleanup_objects ------
