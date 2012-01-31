#-- start of make_header -----------------

#====================================
#  Application magnetnormal
#
#   Generated Mon Jan 30 23:54:38 2012  by phuidn
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_magnetnormal_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_magnetnormal_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_magnetnormal

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_magnetnormal = /tmp/CMT_$(cuts_tag)_magnetnormal.make$(cmt_lock_pid)
else
#cmt_local_tagfile_magnetnormal = $(cuts_tag)_magnetnormal.make
cmt_local_tagfile_magnetnormal = $(bin)$(cuts_tag)_magnetnormal.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_magnetnormal = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_magnetnormal = $(cuts_tag).make
cmt_local_tagfile_magnetnormal = $(bin)$(cuts_tag).make
endif

endif

-include $(cmt_local_tagfile_magnetnormal)

ifdef cmt_magnetnormal_has_target_tag

ifdef READONLY
cmt_final_setup_magnetnormal = /tmp/CMT_cuts_magnetnormalsetup.make
cmt_local_magnetnormal_makefile = /tmp/CMT_magnetnormal$(cmt_lock_pid).make
else
cmt_final_setup_magnetnormal = $(bin)cuts_magnetnormalsetup.make
cmt_local_magnetnormal_makefile = $(bin)magnetnormal.make
endif

else

ifdef READONLY
cmt_final_setup_magnetnormal = /tmp/CMT_cutssetup.make
cmt_local_magnetnormal_makefile = /tmp/CMT_magnetnormal$(cmt_lock_pid).make
else
cmt_final_setup_magnetnormal = $(bin)cutssetup.make
cmt_local_magnetnormal_makefile = $(bin)magnetnormal.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_cutssetup.make
else
cmt_final_setup = $(bin)cutssetup.make
endif

magnetnormal ::


ifdef READONLY
magnetnormal ::
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
	$(echo) 'magnetnormal'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = magnetnormal/
magnetnormal::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

magnetnormal :: dirs  $(bin)magnetnormal${application_suffix}
	$(echo) "magnetnormal ok"

#-- end of application_header
#-- start of application

$(bin)magnetnormal${application_suffix} :: $(bin)maketree.o $(bin)cuts.o $(use_stamps) $(magnetnormalstamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)maketree.o $(bin)cuts.o $(cmt_installarea_linkopts) $(magnetnormal_use_linkopts) $(magnetnormallinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
magnetnormalinstallname = magnetnormal${application_suffix}

magnetnormal :: magnetnormalinstall

install :: magnetnormalinstall

magnetnormalinstall :: $(install_dir)/$(magnetnormalinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(magnetnormalinstallname) :: $(bin)$(magnetnormalinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(magnetnormalinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##magnetnormalclean :: magnetnormaluninstall

uninstall :: magnetnormaluninstall

magnetnormaluninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(magnetnormalinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (magnetnormal.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),magnetnormalclean)

#$(bin)magnetnormal_dependencies.make :: dirs

ifndef QUICK
$(bin)magnetnormal_dependencies.make : ../app/maketree.C ../app/cuts.C $(use_requirements) $(cmt_final_setup_magnetnormal)
	$(echo) "(magnetnormal.make) Rebuilding $@"; \
	  $(build_dependencies) magnetnormal -all_sources -out=$@ ../app/maketree.C ../app/cuts.C
endif

#$(magnetnormal_dependencies)

-include $(bin)magnetnormal_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)magnetnormal_dependencies.make : $(maketree_C_dependencies)

$(bin)$(binobj)maketree.o : $(maketree_C_dependencies)
	$(cpp_echo) ../app/maketree.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(magnetnormal_pp_cppflags) $(app_magnetnormal_pp_cppflags) $(maketree_pp_cppflags) $(use_cppflags) $(magnetnormal_cppflags) $(app_magnetnormal_cppflags) $(maketree_cppflags) $(maketree_C_cppflags) -I../app ../app/maketree.C

#-- end of cpp ------
#-- start of cpp ------

$(bin)magnetnormal_dependencies.make : $(cuts_C_dependencies)

$(bin)$(binobj)cuts.o : $(cuts_C_dependencies)
	$(cpp_echo) ../app/cuts.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(magnetnormal_pp_cppflags) $(app_magnetnormal_pp_cppflags) $(cuts_pp_cppflags) $(use_cppflags) $(magnetnormal_cppflags) $(app_magnetnormal_cppflags) $(cuts_cppflags) $(cuts_C_cppflags) -I../app ../app/cuts.C

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: magnetnormalclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(magnetnormal.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(magnetnormal.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_magnetnormal)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(magnetnormal.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(magnetnormal.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(magnetnormal.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

magnetnormalclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) magnetnormal${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f magnetnormal${application_suffix}

#	@echo "------> (magnetnormal.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)maketree.o $(bin)cuts.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf magnetnormal_deps magnetnormal_dependencies.make
#-- end of cleanup_objects ------
