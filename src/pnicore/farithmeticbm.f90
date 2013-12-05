program farithmeticbm 
    use benchmark
    use arithmetic_benchmark
    implicit none
    real(kind=8),dimension(:),allocatable :: add_results
    real(kind=8),dimension(:),allocatable :: sub_results
    real(kind=8),dimension(:),allocatable :: div_results
    real(kind=8),dimension(:),allocatable :: mult_results
    real(kind=8),dimension(:),allocatable :: mix_results
    integer :: nx,ny,nruns,i
    integer :: ai !argument index
    character(len=256) :: arg

    !set default values
    nx = 4096
    ny = 4096
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
    call allocate_benchmark_results(nruns,add_results)
    call allocate_benchmark_results(nruns,sub_results)
    call allocate_benchmark_results(nruns,div_results)
    call allocate_benchmark_results(nruns,mult_results)
    call allocate_benchmark_results(nruns,mix_results)
    call allocate_arithmetics(nx,ny)

    !run the add benchmarks    
    call run_benchmarks(run_add,add_results)
        
    !run the sub benchmarks
    call run_benchmarks(run_sub,sub_results)

    !run the div benchmarks
    call run_benchmarks(run_div,div_results)

    !run the mult benchmarks
    call run_benchmarks(run_mult,mult_results)

    !run the all benchmark
    call run_benchmarks(run_all,mix_results)

    !print all the results
    add_results = add_results*1.d+9;
    sub_results = sub_results*1.d+9;
    div_results = div_results*1.d+9;
    mult_results = mult_results*1.d+9;
    mix_results = mix_results*1.d+9;
    do i=1,nruns
    write(*,'(E23.16,E23.16,E23.16,E23.16,E23.16)') add_results(i),sub_results(i),div_results(i),mult_results(i),mix_results(i)
    end do


    !in the end we have to free everything
    call deallocate_benchmark_results(add_results)
    call deallocate_benchmark_results(sub_results)
    call deallocate_benchmark_results(div_results)
    call deallocate_benchmark_results(mult_results)
    call deallocate_benchmark_results(mix_results)

    call deallocate_arithmetics()

end program farithmeticbm
