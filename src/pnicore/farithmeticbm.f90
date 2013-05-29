program farithmeticbm 
    use benchmark
    use arithmetic_benchmark
    implicit none
    real(kind=8),dimension(:),allocatable :: results
    integer :: nx,ny,nruns
    integer :: ai !argument index
    character(len=256) :: arg

    !set default values
    nx = 2000
    ny = 2000
    nruns = 10

    !parse command line arguments
    cli_parse: do ai = 1,command_argument_count()
        call get_command_argument(ai,arg)

        if (index(arg,"-r")==1) then 
            read(arg(3:),'(I10)') nruns
        else if (index(arg,"--nruns=")==1) then
            read(arg(9:),'(I10)') nruns
        else if (index(arg,"-x")==1) then
            read(arg(3:),'(I10)') nx
        else if (index(arg,"--nx=")==1) then
            read(arg(6:),'(I10)') nx
        else if (index(arg,"-y")==1) then
            read(arg(3:),'(I10)') ny
        else if (index(arg,"--ny=")==1) then
            read(arg(6:),'(I10)') ny
        else 
            write (*,*) 'unknown command line or unknown syntax'
        end if

    end do cli_parse


    !allocate memory
    call allocate_benchmark_results(nruns,results)
    call allocate_arithmetics(nx,ny)

    !run the add benchmarks    
    call run_benchmarks(run_add,results)
    call print_result('c=(a+b)',results)
    results = 0.d0
        
    !run the sub benchmarks
    call run_benchmarks(run_sub,results)
    call print_result('c=(a-b)',results)
    results = 0.d0

    !run the div benchmarks
    call run_benchmarks(run_div,results)
    call print_result('c=(a/b)',results)
    results = 0.d0

    !run the mult benchmarks
    call run_benchmarks(run_mult,results)
    call print_result('c=a*b',results)
    results = 0.d0

    !run the all benchmark
    call run_benchmarks(run_all,results)
    call print_result('c=a*b+(d-e)/f',results)
    results = 0.d0


    !in the end we have to free everything
    call deallocate_benchmark_results(results)
    call deallocate_arithmetics()

end program farithmeticbm
