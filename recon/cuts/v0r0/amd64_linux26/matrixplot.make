#-- start of make_header -----------------

#====================================
#  Application matrixplot
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

cmt_matrixplot_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_matrixplot_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_matrixplot

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_matrixplot = /tmp/CMT_$(cuts_tag)_matrixplot.make$(cmt_lock_pid)
else
#cmt_local_tagfile_matrixplot = $(cuts_tag)_matrixplot.make
cmt_local_tagfile_matrixplot = $(bin)$(cuts_tag)_matrixplot.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_matrixplot = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_matrixplot = $(cuts_tag).make
cmt_local_tagfile_matrixplot = $(bin)$(cuts_tag).make
endif

endif

-include $(cmt_local_tagfile_matrixplot)

ifdef cmt_matrixplot_has_target_tag

ifdef READONLY
cmt_final_setup_matrixplot = /tmp/CMT_cuts_matrixplotsetup.make
cmt_local_matrixplot_makefile = /tmp/CMT_matrixplot$(cmt_lock_pid).make
else
cmt_final_setup_matrixplot = $(bin)cuts_matrixplotsetup.make
cmt_local_matrixplot_makefile = $(bin)matrixplot.make
endif

else

ifdef READONLY
cmt_final_setup_matrixplot = /tmp/CMT_cutssetup.make
cmt_local_matrixplot_makefile = /tmp/CMT_matrixplot$(cmt_lock_pid).make
else
cmt_final_setup_matrixplot = $(bin)cutssetup.make
cmt_local_matrixplot_makefile = $(bin)matrixplot.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_cutssetup.make
else
cmt_final_setup = $(bin)cutssetup.make
endif

matrixplot ::


ifdef READONLY
matrixplot ::
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
	$(echo) 'matrixplot'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = matrixplot/
matrixplot::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

matrixplot :: dirs  $(bin)matrixplot${application_suffix}
	$(echo) "matrixplot ok"

#-- end of application_header
#-- start of application

$(bin)matrixplot${application_suffix} :: $(bin)matrix.o $(use_stamps) $(matrixplotstamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)matrix.o $(cmt_installarea_linkopts) $(matrixplot_use_linkopts) $(matrixplotlinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
matrixplotinstallname = matrixplot${application_suffix}

matrixplot :: matrixplotinstall

install :: matrixplotinstall

matrixplotinstall :: $(install_dir)/$(matrixplotinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(matrixplotinstallname) :: $(bin)$(matrixplotinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(matrixplotinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##matrixplotclean :: matrixplotuninstall

uninstall :: matrixplotuninstall

matrixplotuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(matrixplotinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (matrixplot.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),matrixplotclean)

#$(bin)matrixplot_dependencies.make :: dirs

ifndef QUICK
$(bin)matrixplot_dependencies.make : ../app/matrix.C $(use_requirements) $(cmt_final_setup_matrixplot)
	$(echo) "(matrixplot.make) Rebuilding $@"; \
	  $(build_dependencies) matrixplot -all_sources -out=$@ ../app/matrix.C
endif

#$(matrixplot_dependencies)

-include $(bin)matrixplot_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)matrixplot_dependencies.make : $(matrix_C_dependencies)

$(bin)$(binobj)matrix.o : $(matrix_C_dependencies)
	$(cpp_echo) ../app/matrix.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(matrixplot_pp_cppflags) $(app_matrixplot_pp_cppflags) $(matrix_pp_cppflags) $(use_cppflags) $(matrixplot_cppflags) $(app_matrixplot_cppflags) $(matrix_cppflags) $(matrix_C_cppflags) -I../app ../app/matrix.C

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: matrixplotclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(matrixplot.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(matrixplot.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_matrixplot)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(matrixplot.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(matrixplot.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(matrixplot.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

matrixplotclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) matrixplot${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f matrixplot${application_suffix}

#	@echo "------> (matrixplot.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)matrix.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf matrixplot_deps matrixplot_dependencies.make
#-- end of cleanup_objects ------
